/**
 * Interface Segregation Principle (ISP):
 * No client should be forced to depend on interfaces they don't use.
 * 
 *  * The main idea behind ISP is to prevent "fat" or "bloated" interfaces
 *    that contain methods that are not required by clients.
 */

#include <iostream>

/**
 * Code Example:
 *  - Let's consider a scenario where we have a media player application
 *    that supports different types of media files, such as audio files
 *    (MP3, WAV) and video files (MP4, AVI).
 * 
 *  - Without applying the ISP. We might have a single interface called MediaPlayer
 */

 class MediaPlayer {
public:
   void playAudio(const std::string& audioFile) {
       std::cout << "Playing audio file: " << audioFile << std::endl;
   }

   void playVideo(const std::string& videoFile) {
       std::cout << "Playing video file: " << videoFile << std::endl;
   }

   void stopAudio() {
       std::cout << "Stopping audio playback." << std::endl;
   }

    void stopVideo() {
         std::cout << "Stopping video playback." << std::endl;
    }

    void adjustAudioVolume(int volume) {
        std::cout << "Adjusting audio volume to: " << volume << std::endl;
    }

    void adjustVideoBrightness(int brightness) {
        std::cout << "Adjusting video brightness to: " << brightness << std::endl;
    }
 };

 /**
  * In this case, any client need to implement the MediaPlayer interface
  * will be forced to implement methods that are not relevant to them.
  */

// To adhere the ISP, we can segregate the MediaPlayer interface into smaller, more focused interfaces.
class AudioPlayer {
public:
    virtual void playAudio(const std::string& audioFile) = 0;
    virtual void stopAudio() = 0;
    virtual void adjustAudioVolume(int volume) = 0;
    virtual ~AudioPlayer() {}
};

class VideoPlayer {
public:
    virtual void playVideo(const std::string& videoFile) = 0;
    virtual void stopVideo() = 0;
    virtual void adjustVideoBrightness(int brightness) = 0;
    virtual ~VideoPlayer() {}
};

// Now, we can have separate implementations for audio and video players:
class MP3Player : public AudioPlayer {
public:
    void playAudio(const std::string& audioFile) override {
        std::cout << "Playing MP3 audio file: " << audioFile << std::endl;
    }

    void stopAudio() override {
        std::cout << "Stopping MP3 audio playback." << std::endl;
    }

    void adjustAudioVolume(int volume) override {
        std::cout << "Adjusting MP3 audio volume to: " << volume << std::endl;
    }
};

class MP4Player : public VideoPlayer {
public:
    void playVideo(const std::string& videoFile) override {
        std::cout << "Playing MP4 video file: " << videoFile << std::endl;
    }

    void stopVideo() override {
        std::cout << "Stopping MP4 video playback." << std::endl;
    }

    void adjustVideoBrightness(int brightness) override {
        std::cout << "Adjusting MP4 video brightness to: " << brightness << std::endl;
    }
};

// if we need a class that supports both audio and video playback, we can create a new class 
// that implements both interfaces:
class MultimediaPlayer : public AudioPlayer, public VideoPlayer {
// Implement methods for both audioPlayer and videoPlayer interfaces
};