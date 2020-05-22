all:
	sudo apt-get install libsfml-dev
	g++ main_bot.cpp -o snake_bot snake/lib/snake_model.cpp snake/lib/snake_bot.cpp snake/lib/snake_view.cpp -lsfml-graphics -lsfml-system -lsfml-window
	g++ main_user.cpp -o snake_user snake/lib/snake_model.cpp snake/lib/snake_controller.cpp snake/lib/snake_view.cpp -lsfml-graphics -lsfml-system -lsfml-window
	./snake_bot 40 40 18 10 40 1000 2
