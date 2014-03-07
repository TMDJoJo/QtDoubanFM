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
//    volume_slider_ = new Phonon::VolumeSlider();
//    Q_ASSERT(volume_slider_);
//    volume_slider_->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
//    volume_slider_->setAudioOutput(audio_output_);

    Phonon::createPath(media_object_,audio_output_);

    connect(media_object_,SIGNAL(tick(qint64)),
            this,SLOT(OnTick(qint64)));
    connect(media_object_, SIGNAL(stateChanged(Phonon::State, Phonon::State)),
            this, SLOT(OnStateChanged(Phonon::State, Phonon::State)));

    connect(media_object_, SIGNAL(aboutToFinish()), this, SLOT(OnAboutToFinish()));
    connect(media_object_, SIGNAL(currentSourceChanged(const Phonon::MediaSource&)),
            this,SLOT(OnCurrentSourceChanged(const Phonon::MediaSource&)));
}

Music::~Music(){
    if(NULL != media_object_){
        media_object_->stop();
    }
    SAFE_DELETE(audio_output_);
    SAFE_DELETE(media_object_);

    if(NULL != song_list_){
        while(!song_list_->isEmpty()){
            SAFE_DELETE(song_list_->front());
            song_list_->pop_front();
        }
    }

    SAFE_DELETE(song_list_);
    SAFE_DELETE(current_song_);
}

void Music::OnTick(qint64 play_time){
    emit PlayTimeTick(play_time,RemainingTime());
}

void Music::OnStateChanged(Phonon::State new_state, Phonon::State old_state){
    //Phonon::AudioOutputDeviceType 0
    //Phonon::StoppedState          1
    //Phonon::PlayingState          2
    //Phonon::BufferingState        3
    //Phonon::PausedState           4
    //Phonon::ErrorState            5

    emit StateChanged((Music_State)new_state,(Music_State)old_state);
}
//http://zonyitoo.github.io/blog/2013/01/22/doubanfmbo-fang-qi-kai-fa-shou-ji/
//https://github.com/ginuerzh/qDoubanFM
void Music::OnAboutToFinish(){
    if(NULL != current_song_)
        emit SongAboutFinish();
    if(song_list_->isEmpty()){
        //// end of a list
        emit ListEmpty();
    }
    else{

        media_object_->enqueue(QUrl(song_list_->front()->url_));
    }
}

void Music::OnCurrentSourceChanged(const Phonon::MediaSource&){
    ////开始播放下一曲
    SAFE_DELETE(current_song_);
    current_song_ = song_list_->front();
    song_list_->pop_front();
    emit PlaySong(current_song_);
}

bool Music::set_song_list(SongList* song_list){
    if(NULL == song_list)
        return false;
    if(song_list_ != NULL){
        while(!song_list_->isEmpty()){
            SAFE_DELETE(song_list_->front());
            song_list_->pop_front();
        }
        SAFE_DELETE(song_list_);
    }
    song_list_ = song_list;
    return true;
}

qint64 Music::PlayTime(){
    if(NULL == media_object_)
        return 0;
    return media_object_->currentTime();
}

qint64 Music::RemainingTime(){
    if(NULL == media_object_)
        return 0;
    return media_object_->remainingTime();
}

bool Music::Next(){
    if(NULL == song_list_
        || song_list_->isEmpty()){
        emit ListEmpty();
        return false;
    }
//    current_song_ = song_list_->front();
//    song_list_->pop_front();

    media_object_->setCurrentSource(QUrl(song_list_->front()->url_));
    media_object_->play();


    return true;
}

void Music::SetVolume(quint8 value){
    qreal v = float(value)/100;
    audio_output_->setVolume(v);
}

void Music::Pause(){
    if(media_object_->state() == Phonon::PlayingState)
        media_object_->pause();
}

void Music::Play(){
    if(media_object_->state() == Phonon::PausedState)
        media_object_->play();
}
