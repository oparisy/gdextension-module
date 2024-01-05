#ifndef AUDIOSTREAM_MODULE_H
#define AUDIOSTREAM_MODULE_H

// We don't need windows.h in this plugin but many others do and it throws up on itself all the time
// So best to include it and make sure CI warns us when we use something Microsoft took for their own goals....
#ifdef WIN32
#include <windows.h>
#endif

#include <xmp.h>

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/audio_stream.hpp>
#include <godot_cpp/classes/audio_stream_playback.hpp>
#include <godot_cpp/variant/string.hpp>

// Required as per https://github.com/godotengine/godot-cpp/issues/1207
#include <godot_cpp/classes/audio_frame.hpp>

using namespace godot;

/**
 * "All audio resources require two audio based classes: AudioStream and AudioStreamPlayback.
 *  As a data container, AudioStream contains the resource and exposes itself to GDScript.
 *  AudioStream references its own internal custom AudioStreamPlayback which translates
 *  AudioStream into PCM data."
 */
class AudioStreamModule : public AudioStream {
    GDCLASS(AudioStreamModule, AudioStream)
    friend class AudioStreamPlaybackModule;
    friend class ResourceFormatLoaderModule;

private:
	PackedByteArray data; // Owned instance

public:
    AudioStreamModule();
    Ref<AudioStreamPlayback> _instantiate_playback() const override;

    // Generate "size" PCM samples in "pcm_buf"
    //void gen_tone(int16_t *pcm_buf, int size);

protected:
	void set_data(const PackedByteArray &p_data);
	const PackedByteArray& get_data() const;

    static void _bind_methods();
};

class AudioStreamPlaybackModule : public AudioStreamPlayback {
    GDCLASS(AudioStreamPlaybackModule, AudioStreamPlayback)
    friend class AudioStreamModule;

private:
    Ref<AudioStreamModule> audioStream; // Keep track of the AudioStream which instantiated us
    const int mix_rate;
    bool active; // Are we currently playing?
    void *pcm_buffer;
    xmp_context ctx;
    xmp_module_info info;

    // Performance-related fields
    Array stats;
    uint64_t last_stats_log;

public:
    AudioStreamPlaybackModule();
    ~AudioStreamPlaybackModule();

    /**
     * "AudioStreamPlayer uses mix callback to obtain PCM data.
     *  The callback must match sample rate and fill the buffer.
     *  Since AudioStreamPlayback is controlled by the audio thread,
     *  i/o and dynamic memory allocation are forbidden."
    */
    int32_t _mix(AudioFrame *buffer, double rate_scale, int32_t frames) override;

    bool _is_playing() const override;
    void _start(double from_pos) override;
    void _seek(double position) override;
    void _stop() override;

protected:
    void setAudioStream(Ref<AudioStreamModule> audioStream);
    static void _bind_methods();
};

#endif // AUDIOSTREAM_MODULE_H