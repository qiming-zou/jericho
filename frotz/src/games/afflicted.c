/*
Copyright (C) 2018 Microsoft Corporation

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <string.h>
#include "frotz.h"
#include "games.h"
#include "frotz_interface.h"

// Afflicted: http://ifdb.tads.org/viewgame?id=epl4q2933rczoo9x

int score = 0;

char** afflicted_intro_actions(int *n) {
  *n = 0;
  return NULL;
}

void parse_score(char* obs) {
  char* pch = obs;
  char* old = pch;
  while (TRUE) {
    pch = strchr(pch, ':');
    if (pch == NULL) {
      break;
    }
    pch++;
    old = pch;
  }
  score = -strtol(old, &old, 10);
}

char* afflicted_clean_observation(char* obs) {
  parse_score(obs);
  char* pch;
  pch = strchr(obs, '>');
  if (pch != NULL) {
    *(pch-2) = '\0';
  }
  return obs+1;
}

int afflicted_victory() {
  char *death_text = "*** You have won ***";
  if (strstr(world, death_text)) {
    return 1;
  }
  return 0;
}

int afflicted_game_over() {
  char *death_text = "*** You've been convicted. ***";
  if (strstr(world, death_text)) {
    return 1;
  }
  return 0;
}

int afflicted_get_self_object_num() {
  return 57;
}

int afflicted_get_moves() {
  return (((short) zmp[24991]) << 8) | zmp[24992]; // 25032, 25034
}

short afflicted_get_score() {
  return score;
}

int afflicted_max_score() {
  return 75;
}

int afflicted_get_num_world_objs() {
  return 237;
}

int afflicted_ignore_moved_obj(zword obj_num, zword dest_num) {
  return 0;
}

int afflicted_ignore_attr_diff(zword obj_num, zword attr_idx) {
  if (attr_idx == 30 || attr_idx == 11 || attr_idx == 34 || attr_idx == 21)
    return 1;
  return 0;
}

int afflicted_ignore_attr_clr(zword obj_num, zword attr_idx) {
  if (attr_idx == 30)
    return 1;
  return 0;
}

void afflicted_clean_world_objs(zobject* objs) {
}
