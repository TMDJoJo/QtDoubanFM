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

    connect(g_music,SIGNAL(GetNewList()),
            this,SLOT(OnReceiveNewList()));
}

bool ActionDispatch::ActionSong(IActor* actor,ActionFactory::ActionType type){
    SongAction* action = dynamic_cast<SongAction*>(
                ActionFactory::CreateAction(actor,type)
                );
    action->Excute();
    SAFE_DELETE(action);
    return true;
}

void ActionDispatch::OnReceivedNewList(SongList* song_list){

    g_music->set_song_list(song_list);
}

void ActionDispatch::OnReceiveNewList(){
    ////当前列表播放接受后继续获得下一列表
    g_douban_web->GetNewList();
}
