all: AutoBattleC++.o Battlefield.o Character.o Grid.o Types.o
	gcc AutoBattleC++.o Battlefield.o Character.o Grid.o Types.o -o AutoBattle
AutoBattleC++.o: AutoBattleC++.cpp
	gcc AutoBattleC++.cpp -c
Battlefield.o: Battlefield.c
	gcc Battlefield.cpp -c
Character.o: Character.cpp
	gcc Character.cpp -c
Grid.o: Grid.cpp
	gcc Grid.cpp -c
Types.o: Types.cpp
	gcc Types.cpp -c
run:
	./AutoBattle
clean:
	rm -rf AutoBattle *.o