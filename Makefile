all: AutoBattleC++.o BattleField.o Character.o Grid.o Types.o
	g++ AutoBattleC++.o BattleField.o Character.o Grid.o Types.o -o AutoBattle
AutoBattleC++.o: AutoBattleC++.cpp
	g++ AutoBattleC++.cpp -c
Battlefield.o: BattleField.cpp
	g++ BattleField.cpp -c
Character.o: Character.cpp
	g++ Character.cpp -c
Grid.o: Grid.cpp
	g++ Grid.cpp -c
Types.o: Types.cpp
	g++ Types.cpp -c
run:
	./AutoBattle
clean:
	rm -rf AutoBattle *.o