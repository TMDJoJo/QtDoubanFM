#ifndef MUSIC_H
#define MUSIC_H

#include <QObject>
#include <Phonon>
#include "../Type/DouBanSong.h"

class Music : public QObject
{
    Q_OBJECT
public:
    explicit Music(QObject *parent = 0);

    bool set_song_list(SongList* song_list);

    const DouBanSong* current_song(){ return current_song_; }
    qint64 PlayTime();
    bool Next();
    void SetVolume(quint8);
signals:
    void EmptyList();
    void PlayTimeTick(qint64);
    void PlaySong(DouBanSong* song);
private slots:
    void OnTick(qint64);
    void OnStateChanged(Phonon::State new_state, Phonon::State old_state);
    void OnAboutToFinish();

private:
    Phonon::AudioOutput* audio_output_;
    Phonon::MediaObject* media_object_;
//    Phonon::VolumeSlider* volume_slider_;
    DouBanSong* current_song_;
    SongList* song_list_;
};

extern Music* g_music;

#endif // MUSIC_H
