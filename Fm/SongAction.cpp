#include "SongAction.h"
#include <QDebug>

#include "./Fm/Web/DouBanWeb.h"
#include <QNetworkReply>

SongAction::SongAction(IActor* actor) :
    IAction(actor)
{

}

bool SongAction::Excute(){

    if(type_ == ActionFactory::SONG_NEXT){
        return NextSong();
    }
    else if(type_ == ActionFactory::SONG_TRASH){
        return TrashSong();
    }
    else if(type_ == ActionFactory::SONG_LIKE){
        return LikeSong();
    }
    else if(type_ == ActionFactory::SONG_PAUSE){
        return false;
    }
    else{
        return false;
    }
}

bool SongAction::NextSong(){
    qDebug()<<"next";

    return g_douban_web->GetNewList();
}

bool SongAction::LikeSong(){
    qDebug()<<"llke";

    return g_douban_web->LikeSong();
}

bool SongAction::TrashSong(){
    qDebug()<<"trash";

    return g_douban_web->TrashSong();
}
