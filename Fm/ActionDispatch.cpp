#include "ActionDispatch.h"

#include "./Web/DouBanWeb.h"
#include "./Music/Music.h"

const QChar GET_SONG_SKIP = 's';        ////return song list
const QChar GET_SONG_RATE = 'r';        ////return song list
const QChar GET_SONG_UNRATE = 'u';      ////return song list
const QChar GET_SONG_END = 'e';         ////return {"r":0}
const QChar GET_SONG_NEW = 'n';         ////return song list
const QChar GET_SONG_BYE = 'b';         ////return song list
const QChar GET_SONG_PLAY = 'p';        ////return song list
ActionDispatch* g_action_dispatch = NULL;

ActionDispatch::ActionDispatch(QObject *parent) :
    QObject(parent),
    is_next_(false)
{
    connect(g_douban_web,SIGNAL(ReceivedNewList(SongList*)),
            this,SLOT(OnReceivedNewList(SongList*)));
    connect(g_douban_web,SIGNAL(ReceivedAlbumPicture(QPixmap*)),
            this,SLOT(OnReceivedAlbumPicture(QPixmap*)));

    connect(g_douban_web,SIGNAL(ReceivedHotChannels(ChannelList*)),
            this,SLOT(OnReceivedHotChannels(ChannelList*)));
    connect(g_douban_web,SIGNAL(ReceivedFastChannels(ChannelList*)),
            this,SLOT(OnReceivedFastChannels(ChannelList*)));

    connect(g_music,SIGNAL(ListEmpty()),
            this,SLOT(OnEmptyList()));
    connect(g_music,SIGNAL(PlayTimeTick(qint64,qint64)),
            this,SLOT(OnPlayTimeTick(qint64,qint64)));
    connect(g_music,SIGNAL(PlaySong(DouBanSong*)),
            this,SLOT(OnPlaySong(DouBanSong*)));
    connect(g_music,SIGNAL(SongAboutFinish()),
            this,SLOT(OnSongAboutFinish()));

    //ChangeChannel(0,0);
    GetChannelId();
}

bool ActionDispatch::set_play_scene(PlayScene* play_scene){
    if(NULL == play_scene)
        return false;
    play_scene_ = play_scene;
    return true;
}

bool ActionDispatch::set_channel_scene(ChannelScene* channel_scene){
    if(NULL == channel_scene_)
        return false;
    channel_scene_ = channel_scene;
    return true;
}

void ActionDispatch::Next(){
    if(NULL == g_music->current_song())
        return;
    QString song_id = g_music->current_song()->sid_;
    QString play_time = QString("%1").arg(float(g_music->PlayTime()/100)/10);
    QString type = GET_SONG_SKIP;
    QString arg = QString("type=%1"
                          "&sid=%2"
                          "&pt=%3"
                          "&channel=%4"
                          "&pb=%5"
                          "&from=%6").arg(
                type,song_id,play_time,QString::number(channel_scene_->current_channel_id()),QString::number(64),"mainsite");
    g_douban_web->GetNewList(arg);
    is_next_ = true;
}

void ActionDispatch::Like(bool like){
    if(NULL == g_music->current_song()
            ||NULL == channel_scene_)
        return;
    QString song_id = g_music->current_song()->sid_;
    QString play_time = QString("%1").arg(float(g_music->PlayTime()/100)/10);
    QString type = "";
    if(like){
        type = GET_SONG_RATE;
    }
    else{
        type = GET_SONG_UNRATE;
    }
    QString arg = QString("type=%1"
                          "&sid=%2"
                          "&pt=%3"
                          "&channel=%4"
                          "&pb=%5"
                          "&from=%6").arg(
                type,song_id,
                play_time,
                QString::number(channel_scene_->current_channel_id()),
                QString::number(64),"mainsite");
    g_douban_web->LikeSong(arg);
}

void ActionDispatch::Trash(){
    if(g_music->current_song() == NULL
            ||NULL == channel_scene_)
        return;
    QString song_id = g_music->current_song()->sid_;
    QString play_time = QString("%1").arg(float(g_music->PlayTime()/100)/10);
    QString type = GET_SONG_BYE;
    QString arg = QString("type=%1"
                          "&sid=%2"
                          "&pt=%3"
                          "&channel=%4"
                          "&pb=%5"
                          "&from=%6").arg(
                type,song_id,play_time,
                QString::number(channel_scene_->current_channel_id()),
                QString::number(64),"mainsite");
    g_douban_web->TrashSong(arg);
    is_next_ = true;
}

void ActionDispatch::SetVolume(quint8 value){
    g_music->SetVolume(value);
}

void ActionDispatch::GetChannelId(){
    QString arg = "http://douban.fm";
    g_douban_web->GetChannelId(arg);
}

void ActionDispatch::Pause(){
    g_music->Pause();
}

void ActionDispatch::Play(){
    g_music->Play();
}

void ActionDispatch::ChangeChannel(quint32 /*from_channel_id*/,quint32 to_channel_id){
    //第一次开始：http://douban.fm/j/mine/playlist?type=n&sid=&pt=0.0&channel=153&from=mainsite&r=9147f37e03
    QString song_id = "";
    if(g_music->current_song() != NULL)
        song_id = g_music->current_song()->sid_;
    QString play_time = QString("%1").arg(float(g_music->PlayTime()/100)/10);
    QString type = GET_SONG_NEW;
    QString arg = QString("type=%1"
                          "&sid=%2"
                          "&pt=%3"
                          "&channel=%4"
                          "&pb=%5"
                          "&from=%6").arg(
                type,
                song_id,play_time,
                QString::number(to_channel_id),QString::number(64),
                "mainsite");
    g_douban_web->GetNewList(arg);
    is_next_ = true;
}

void ActionDispatch::OnReceivedAlbumPicture(QPixmap* picture){
    if(NULL == picture)
        return;
    play_scene_->SetAlbumPicture(picture);
}

void ActionDispatch::OnReceivedNewList(SongList* song_list){
    ////获得播放列表完成，将其设置给播放器
    g_music->set_song_list(song_list);
    if(is_next_){
        g_music->Next();
        is_next_ = false;
    }
}

void ActionDispatch::OnEmptyList(){
    ////播放列表放完以后，重新get新列表
    ////http://douban.fm/j/mine/playlist?type=p&sid=376729&pt=0.0&channel=170&pb=64&from=mainsite&r=76ff5c9fcc
    QString song_id = "";
    if(g_music->current_song() != NULL)
        song_id = g_music->current_song()->sid_;
    QString play_time = QString("%1").arg(float(g_music->PlayTime()/100)/10);
    QString type = GET_SONG_NEW;

    QString arg = QString("type=%1&sid=%2&pt=%3&channel=%4&pb=%5&from=%6").arg(
                type,song_id,play_time,QString::number(channel_scene_->current_channel_id()),QString::number(64),"mainsite");
    ////当前列表播放接受后继续获得下一列表
    g_douban_web->GetNewList(arg);
    is_next_ = true;
}

void ActionDispatch::OnPlayTimeTick(qint64 play_time,qint64 remaining_time){
    ////
    play_scene_->set_play_time(play_time,remaining_time);
}

void ActionDispatch::OnPlaySong(DouBanSong* song){
    ////
    if(NULL == song)
        return;
    ////将低清图地址http://img3.douban.com/mpic/s2693584.jpg
    ////转为 高清图地址http://img3.douban.com/lpic/s2693584.jpg
    QString pic_url = song->picture_.replace("mpic","lpic");
    g_douban_web->GetAlbumPicture(pic_url);
    play_scene_->SetSongInfo(song);
}

void ActionDispatch::OnSongAboutFinish(){
    ////TODO: play end of a song
    //http://douban.fm/j/mine/playlist?type=e&sid=549095&channel=170&pt=107.7&pb=64&from=mainsite&r=778a1ca772
    const DouBanSong* current_song = g_music->current_song();
    if(NULL == current_song
            ||NULL == channel_scene_)
        return;
    QString song_id = current_song->sid_;
    QString channel_id = QString::number(channel_scene_->current_channel_id());
    QString play_time = QString("%1").arg(float(current_song->length_)/1);
    QString type = GET_SONG_END;
    QString arg = QString("type=%1"
                          "&sid=%2"
                          "&pt=%3"
                          "&channel=%4"
                          "&pb=%5"
                          "&from=%6").arg(
                type,
                song_id,play_time,
                channel_id,QString::number(64),
                "mainsite");
    g_douban_web->GetNewList(arg);
}

void ActionDispatch::OnReceivedHotChannels(ChannelList* channel_list){
    ////channel_scene_
    if(NULL == channel_list)
        return;
    while(!channel_list->isEmpty()){
        DouBanChannel* channel = channel_list->front();
        channel_list->pop_front();
        if(NULL == channel)
            continue;
        channel_scene_->AddHotChannel(channel);
        ////TODO: set channel cover
    }
    SAFE_DELETE(channel_list);
}

void ActionDispatch::OnReceivedFastChannels(ChannelList* channel_list){
    ////AddFastChannel
    if(NULL == channel_list)
        return;
    while(!channel_list->isEmpty()){
        DouBanChannel* channel = channel_list->front();
        channel_list->pop_front();
        if(NULL == channel)
            continue;
        channel_scene_->AddFastChannel(channel);
        ////TODO: set channel cover
    }
    SAFE_DELETE(channel_list);
}

