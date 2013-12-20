#include "ActionDispatch.h"

#include "SongAction.h"
#include "./Web/DouBanWeb.h"
#include "./Music/Music.h"

ActionDispatch* g_action_dispatch = NULL;

ActionDispatch::ActionDispatch(QObject *parent) :
    QObject(parent)
{


    connect(g_douban_web,SIGNAL(ReceivedNewList(SongList*)),
            this,SLOT(OnReceivedNewList(SongList*)));
    connect(g_douban_web,SIGNAL(ReceivedAlbumPicture(QPixmap*)),
            this,SLOT(OnReceivedAlbumPicture(QPixmap*)));

    connect(g_music,SIGNAL(GetNewList()),
            this,SLOT(OnReceiveNewList()));
    connect(g_music,SIGNAL(PlayTimeTick(qint64)),
            this,SLOT(OnPlayTimeTick(qint64)));
    connect(g_music,SIGNAL(PlaySong(DouBanSong*)),
            this,SLOT(OnPlaySong(DouBanSong*)));


}

bool ActionDispatch::ActionSong(IActor* actor,ActionFactory::ActionType type){
    SongAction* action = dynamic_cast<SongAction*>(
                ActionFactory::CreateAction(actor,type)
                );
    action->Excute();
    SAFE_DELETE(action);
    return true;
}

bool ActionDispatch::set_play_scene(PlayScene* play_scene){
    if(NULL == play_scene)
        return false;
    play_scene_ = play_scene;
    return true;
}

void ActionDispatch::OnReceivedAlbumPicture(QPixmap* picture){
    if(NULL == picture)
        return;
    play_scene_->SetAlbumPicture(picture);
}

void ActionDispatch::OnReceivedNewList(SongList* song_list){
    ////获得播放列表后将其设置给播放器
    g_music->set_song_list(song_list);
}

void ActionDispatch::OnReceiveNewList(){
    ////当前列表播放接受后继续获得下一列表
    g_douban_web->GetNewList();
}

void ActionDispatch::OnPlayTimeTick(qint64 play_time){
    ////
    play_scene_->set_play_time(play_time);
}

void ActionDispatch::OnPlaySong(DouBanSong* song){
    ////
    if(NULL == song)
        return;
    g_douban_web->GetAlbumPicture(song->picture_);
    play_scene_->SetSongInfo(song);

}
