#ifndef MUSIC_H
#define MUSIC_H

#include <QObject>
#include <Phonon>
#include "../Type/DouBanSong.h"

class Music : public QObject
{
    Q_OBJECT
public:
    enum Music_State{
        AudioOutputDeviceType    = 0,
        StoppedState                ,
        PlayingState                ,
        BufferingState              ,
        PausedState                 ,
        ErrorState
    };
public:
    explicit Music(QObject *parent = 0);
    ~Music();

    bool set_song_list(SongList* song_list);

    const DouBanSong* current_song(){ return current_song_; }
    qint64 PlayTime();
    qint64 RemainingTime();

    bool Next();
    void SetVolume(quint8);

    void Pause();
    void Play();
signals:
    void ListEmpty();
    void PlayTimeTick(qint64 play_time,qint64 remaining_time);
    void PlaySong(DouBanSong* song);
    void SongAboutFinish();

    void StateChanged(Music_State new_state, Music_State old_state);
private slots:
    void OnTick(qint64);
    void OnStateChanged(Phonon::State new_state, Phonon::State old_state);
    void OnAboutToFinish();
    void OnCurrentSourceChanged(const Phonon::MediaSource&);
private:
    Phonon::AudioOutput* audio_output_;
    Phonon::MediaObject* media_object_;
//    Phonon::VolumeSlider* volume_slider_;
    DouBanSong* current_song_;
    SongList* song_list_;
};

extern Music* g_music;

#endif // MUSIC_H
