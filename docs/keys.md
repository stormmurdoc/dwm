| Key | Function | Argument |
| :-: | :-: | :- |
|  j | ACTION##stack |  INC(+1) |
|  k | ACTION##stack |  INC(-1) |
| Super  +  Shift + 0 | tag |  ~0 |
| Super + BackSpace | spawns | dwm_exit.sh |
| Super  +  Shift + BackSpace | spawns | dwm_exit.sh |
| Super + asciicircum | spawns | dmenuunicode |
| Super + Tab | view |   |
| Super + q | killclient |   |
| Super  +  Shift + q | spawns | dwm_exit.sh |
| Super + w | spawns | xdo activate -N $BROWSER  +  +  $BROWSER |
| Super  +  Shift + w | spawns | st -e sudo nmtui |
| Super + e | spawns | xdo activate -N Evolution  +  +  evolution |
| Super + d | spawns | rofi -show-icons -show drun |
| Super  +  Shift + e | spawns | st -e neomutt |
| Super + r | togglescratch |  2 |
| Super  +  Shift + r | spawns | st -e btop |
| Super + t | setlayout |  float |
| Super  +  Shift + t | setlayout |  float |
| Super + z | setlayout |  float |
| Super  +  Shift + z | setlayout |  float |
| Super + u | setlayout |  float |
| Super  +  Shift + u | setlayout |  float |
| Super + i | setlayout |  float |
| Super + o | incnmaster |  +1 |
| Super  +  Shift + o | incnmaster |  -1 |
| Super + p | spawns | mpc toggle |
| Super  +  Shift + p | spawns | passmenu |
| Super + bracketleft | spawns | mpc seek -10 |
| Super  +  Shift + bracketleft | spawns | mpc seek -60 |
| Super + bracketright | spawns | mpc seek +10 |
| Super  +  Shift + bracketright | spawns | mpc seek +60 |
| Super + backslash | view |   |
| Super + a | togglegaps |   |
| Super  +  Shift + a | defaultgaps |   |
| Super + s | togglesticky |   |
| Super + f | togglefullscr |   |
| Super  +  Shift + f | setlayout |  float |
| Super + g | shiftview |  -1 |
| Super  +  Shift + g | shifttag |  -1 |
| Super + h | setmfact |  -0.05 |
| Super + l | setmfact |  +0.05 |
| Super + semicolon | shiftview |  1 |
| Super  +  Shift + semicolon | shifttag |  1 |
| Super  +  Shift + apostrophe | togglesmartgaps |   |
| Super + c | togglescratch |  1 |
| Super + Return | spawns |  |
| Super  +  Shift + Return | togglescratch |  0 |
| Super + y | incrgaps |  +3 |
| Super  +  Shift + y | incrgaps |  -3 |
| Super + b | togglebar |   |
| Super  +  Shift + b | spawns | airpods.sh t |
| Super + m | spawns | st -e ncmpcpp |
| Super + comma | spawns | mpc prev |
| Super  +  Shift + comma | spawns | mpc seek 0% |
| Super + period | spawns | mpc next |
| Super  +  Shift + period | spawns | mpc repeat |
| Super + Left | focusmon |  -1 |
| Super  +  Shift + Left | tagmon |  -1 |
| Super + Right | focusmon |  +1 |
| Super  +  Shift + Right | tagmon |  +1 |
| Super + Page_Up | shiftview |  -1 |
| Super  +  Shift + Page_Up | shifttag |  -1 |
| Super + Page_Down | shiftview |  +1 |
| Super  +  Shift + Page_Down | shifttag |  +1 |
| Super + F2 | spawns | dmenuunicode |
| Super + F3 | spawns | st -e displayselect.sh |
| Super + F6 | spawns | torwrap |
| Super + F7 | spawns | td-toggle |
| Super + F8 | spawns | mailsync |
| Super + F9 | spawns | dmenumount |
| Super + F10 | spawns | dmenuumount |
| Super + space | zoom |   |
| Super  +  Shift + space | togglefloating |   |
| Print | spawns | maim pic-full-$(date '+%y%m%d-%H%M-%S').png |
| Shift + Print | spawns | maimpick |
| Super + Print | spawns | dmenurecord.sh |
| Super  +  Shift + Print | spawns | dmenurecord.sh kill |
| Super + Delete | spawns | dmenurecord.sh kill |
| Super + Scroll_Lock | spawns | killall screenkey  +  +  screenkey & |
| AudioPrev | spawns | mpc prev |
| AudioNext | spawns | mpc next |
| AudioPause | spawns | mpc pause |
| AudioPlay | spawns | mpc play |
| AudioStop | spawns | mpc stop |
| AudioRewind | spawns | mpc seek -10 |
| AudioForward | spawns | mpc seek +10 |
| AudioMedia | spawns | st -e ncmpcpp |
| PowerOff | spawns | dwm_exit.sh |
| Calculator | spawns | st -e bc -l |
| Sleep | spawns | sudo -A zzz |
| WWW | spawns | $BROWSER |
| DOS | spawns | st |
| TaskPane | spawns | st -e btop |
| Mail | spawns | evolution |
| MyComputer | spawns | st -e lfrun / |
| Launch1 | spawns | xset dpms force off |
| TouchpadOff | spawns | synclient TouchpadOff=1 |
| TouchpadOn | spawns | synclient TouchpadOff=0 |
