#include "ActionDispatch.h"

#include "./Web/DouBanWeb.h"
#include "./Music/Music.h"

const QChar GET_SONG_NEXT = 's';        ////return song list
const QChar GET_SONG_LIKE = 'r';        ////return song list
const QChar GET_SONG_UNLIKE = 'u';      ////return song list
const QChar GET_SONG_ENDSONG = 'e';     ////return {"r":0}
const QChar GET_SONG_TRASH = 'b';       ////return song list
const QChar GET_SONG_ENDLIST = 'n';     ////return song list

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

    connect(g_music,SIGNAL(EmptyList()),
            this,SLOT(OnEmptyList()));
    connect(g_music,SIGNAL(PlayTimeTick(qint64)),
            this,SLOT(OnPlayTimeTick(qint64)));
    connect(g_music,SIGNAL(PlaySong(DouBanSong*)),
            this,SLOT(OnPlaySong(DouBanSong*)));

    //OnEmptyList();
    ChangeChannel(0,0);
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
    QString song_id = "";
    if(g_music->current_song() != NULL)
        song_id = g_music->current_song()->sid_;
    QString play_time = QString("%1").arg(float(g_music->PlayTime()/100)/10);
    QString type = GET_SONG_NEXT;
    QString arg = QString("type=%1&sid=%2&pt=%3&channel=%4&pb=%5&from=%6").arg(
                type,song_id,play_time,QString::number(channel_scene_->current_channel_id()),QString::number(64),"mainsite");
    g_douban_web->GetNewList(arg);
    is_next_ = true;
}

void ActionDispatch::Like(bool like){
    QString song_id = "";
    if(g_music->current_song() != NULL)
        song_id = g_music->current_song()->sid_;
    QString play_time = QString("%1").arg(float(g_music->PlayTime()/100)/10);
    QString type = "";
    if(like){
        type = GET_SONG_LIKE;
    }
    else{
        type = GET_SONG_UNLIKE;
    }
    QString arg = QString("type=%1&sid=%2&pt=%3&channel=%4&pb=%5&from=%6").arg(
                type,song_id,play_time,QString::number(channel_scene_->current_channel_id()),QString::number(64),"mainsite");
    g_douban_web->LikeSong(arg);
}

void ActionDispatch::Trash(){
    if(g_music->current_song() == NULL)
        return;
    QString song_id = g_music->current_song()->sid_;
    QString play_time = QString("%1").arg(float(g_music->PlayTime()/100)/10);
    QString type = GET_SONG_TRASH;
    QString arg = QString("type=%1&sid=%2&pt=%3&channel=%4&pb=%5&from=%6").arg(
                type,song_id,play_time,QString::number(channel_scene_->current_channel_id()),QString::number(64),"mainsite");
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
    QString song_id = "";
    if(g_music->current_song() != NULL)
        song_id = g_music->current_song()->sid_;
    QString play_time = QString("%1").arg(float(g_music->PlayTime()/100)/10);
    QString type = GET_SONG_ENDLIST;
    QString arg = QString("type=%1&sid=%2&pt=%3&channel=%4&pb=%5&from=%6").arg(
                type,song_id,play_time,QString::number(to_channel_id),QString::number(64),"mainsite");
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
    QString song_id = "";
    if(g_music->current_song() != NULL)
        song_id = g_music->current_song()->sid_;
    QString play_time = QString("%1").arg(float(g_music->PlayTime()/100)/10);
    QString type = GET_SONG_ENDLIST;

    QString arg = QString("type=%1&sid=%2&pt=%3&channel=%4&pb=%5&from=%6").arg(
                type,song_id,play_time,QString::number(channel_scene_->current_channel_id()),QString::number(64),"mainsite");
    ////当前列表播放接受后继续获得下一列表
    g_douban_web->GetNewList(arg);
    is_next_ = true;
}

void ActionDispatch::OnPlayTimeTick(qint64 play_time){
    ////
    play_scene_->set_play_time(play_time);
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
        SAFE_DELETE(channel);
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
        SAFE_DELETE(channel);
    }
    SAFE_DELETE(channel_list);
}

