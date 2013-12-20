#include "Music.h"

#include <QUrl>

#include "../Common.h"

Music* g_music ;

Music::Music(QObject *parent) :
    QObject(parent),
    current_song_(NULL),
    song_list_(NULL),
    audio_output_(NULL),
    media_object_(NULL)
{
    audio_output_ = new Phonon::AudioOutput(Phonon::MusicCategory, this);//初始化系列变量
    Q_ASSERT(audio_output_);
    media_object_ = new Phonon::MediaObject(this);
    Q_ASSERT(media_object_);
    media_object_->setTickInterval(1000);

    Phonon::createPath(media_object_, audio_output_);

    connect(media_object_, SIGNAL(tick(qint64)), this, SLOT(OnTick(qint64)));
    connect(media_object_, SIGNAL(stateChanged(Phonon::State, Phonon::State)),
            this, SLOT(OnStateChanged(Phonon::State, Phonon::State)));
    connect(media_object_, SIGNAL(aboutToFinish()), this, SLOT(OnAboutToFinish()));
}

void Music::OnTick(qint64 play_time){
    emit PlayTimeTick(play_time);
}

void Music::OnStateChanged(Phonon::State new_state, Phonon::State old_state){
    //Phonon::AudioOutputDeviceType 0
    //Phonon::StoppedState          1
    //Phonon::PlayingState          2
    //Phonon::BufferingState        3
    //Phonon::PausedState           4
    //Phonon::ErrorState            5
    qDebug()<<"state change "<<old_state<<new_state;
}

void Music::OnAboutToFinish(){
    if(song_list_->isEmpty()){
        //// end of a list
        emit GetNewList();
    }
    else{
        Next();
    }
}

bool Music::set_song_list(SongList* song_list){
    if(NULL == song_list)
        return false;
    if(song_list_ != NULL){
        SongList::iterator it = song_list_->begin();
        while(it != song_list_->end()){
            SAFE_DELETE(*it);
            ++it;
        }
        SAFE_DELETE(song_list_);
    }
    song_list_ = song_list;
    return Next();
}

bool Music::Next(){
    if(NULL == song_list_
        || song_list_->isEmpty()){
        emit GetNewList();
        return false;
    }

    if(media_object_->state() == Phonon::PlayingState)
        media_object_->stop();
    SAFE_DELETE(current_song_);
    current_song_ = song_list_->front();
    song_list_->pop_front();
    emit PlaySong(current_song_);

    media_object_->setCurrentSource(QUrl(current_song_->url_));
    media_object_->play();
    return true;
}
