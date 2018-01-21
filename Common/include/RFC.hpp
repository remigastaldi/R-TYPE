#pragma once

namespace RFC
{
  enum Responses
  {
    SUCCESS,
    FAIL,
    PONG,
    FRIEND_LIST,
    PROFIL,
    SHIP_INFO,
    SEARCH_ROOM_INFO,
    ROOM_INFO,
    PLAYER_READY,
    PLAYER_NOT_READY,
    GAME_STARTED,
    ROOM_CREATED
  };

  enum Commands
  {
      PING,
      LOGIN,
      GET_FRIEND,
      GET_PROFIL,
      GET_SHIP_INFO,
      BUY_SHIP_COMPONENT,
      SEARCH_ROOM,
      JOIN_ROOM,
      GET_ROOM_INFO,
      LEAVE_ROOM,
      READY,
      NOT_READY,
      START_GAME,
      SELECT_ROOM_LEVEL,
      CREATE_ROOM,
      KEY_PRESSED
  };

};
