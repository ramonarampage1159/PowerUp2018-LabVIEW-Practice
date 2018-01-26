@echo off

mkdir "Autonomous Plays"

echo user > MGET
echo FRC >> MGET
echo prompt >> MGET
echo cd ^"AutonomousPlays^" >> MGET
echo lcd ^"Autonomous^ Plays^" >> MGET
echo mget * >> MGET
echo qui >> MGET

echo user > MPUT
echo FRC >> MPUT
echo prompt >> MPUT
echo cd ^"AutonomousPlays^" >> MPUT
echo lcd ^"Autonomous^ Plays^" >> MPUT
echo mput * >> MPUT
echo qui >> MPUT