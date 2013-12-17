#include "SongAction.h"
#include <QDebug>

#include "./Net/Web.h"
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


    return true;
}

bool SongAction::LikeSong(){
    qDebug()<<"llke";


    return true;
}

bool SongAction::TrashSong(){
    qDebug()<<"trash";


    return true;
}
