#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
const int N = 4, M = 4;
const int TILESIZE = 64;
const int allmap = 256,
WIDTH = N * TILESIZE,
HEIGHT = M * TILESIZE;
bool g_win = false;
int MAP[N][M];
int MAP2[N][M];
bool showGameOver = false;
enum Direction
{
	Left,
	Right,
	Up,
	Down,
	R
};
class TwoZeroFourEight {
private:
public:
	sf::Vector2i genPos()
	{
		sf::Vector2i v;
		while (1)
		{
			v.x = rand() % N;
			v.y = rand() % M;
			if (MAP[v.y][v.x] == 0)
				break;
		}
		return v;
	}
	TwoZeroFourEight()
	{

	}

	void coutMap()
	{
		for (int a = 0; a<N; a++)
		{
			for (int b = 0; b<M; b++)
				cout << MAP[a][b] << " ";
			cout << "\n";
		}
		cout << "\n";
	}

	int genNewTile()
	{
		int t = rand() % 2;
		if (t == 0)
			return 2;
		else
			return 4;
	}

	void placeNewTile()
	{
		sf::Vector2i p = genPos();
		MAP[p.y][p.x] = genNewTile();
	}
	void loseGame() {

		for (int j = 0; j < M; j++)
		{
			for (int i = 0; i < N - 1; i++)
				MAP2[i][j] = MAP[i][j];
		}
		int count = N * M;
		for (int j = 0; j < M; j++)
		{
			for (int i = 0; i < N - 1; i++)
				if (MAP[i][j] == *MAP2[j]) {
					count++;
				}
		}
		if (count == N * M) {
			sf::err;
		}
	}
	void shift(Direction d)
	{
		bool didShift = 0;
		if (d == Direction::Up)
		{
			for (int j = 0; j<M; j++)
			{
				for (int i = 0; i<N - 1; i++)
					if (MAP[i][j] == 0)
					{
						bool change = 0;
						for (int k = i; k<N - 1; k++)
						{
							MAP[k][j] = MAP[k + 1][j];
							if (MAP[k][j] != 0)
							{
								didShift = 1;
								change = 1;
								cout << "kazymazy";
								loseGame();
							}
						}
						MAP[N - 1][j] = 0;
						if (change) i--;
					}
				for (int i = 0; i<N - 1; i++)
					if (MAP[i][j] == MAP[i + 1][j] && MAP[i][j] != 0)
					{
						didShift = 1;
						for (int k = i; k<N - 1; k++)
							MAP[k][j] = MAP[k + 1][j];
						MAP[N - 1][j] = 0;
						MAP[i][j] *= 2;
					}
			}
		}
		else if (d == Direction::Left)
		{
			for (int i = 0; i<N; i++)
			{
				for (int j = 0; j<M - 1; j++)
					if (MAP[i][j] == 0)
					{
						bool change = 0;
						for (int k = j; k<M - 1; k++)
						{
							MAP[i][k] = MAP[i][k + 1];
							if (MAP[i][k] != 0)
							{
								didShift = 1;
								change = 1;
							}
						}
						MAP[i][M - 1] = 0;
						if (change) j--;
					}
				for (int j = 0; j<N - 1; j++)
					if (MAP[i][j] == MAP[i][j + 1] && MAP[i][j] != 0)
					{
						didShift = 1;
						for (int k = j; k<M - 1; k++)
							MAP[i][k] = MAP[i][k + 1];
						MAP[i][M - 1] = 0;
						MAP[i][j] *= 2;
					}
			}
		}
		else if (d == Direction::R) {
			MAP[2][2] = 2048;
		}
		else if (d == Direction::Down)
		{
			for (int j = 0; j<M; j++)
			{
				for (int i = N - 1; i >= 0; i--)
					if (MAP[i][j] == 0)
					{
						bool change = 0;
						for (int k = i; k>0; k--)
						{
							MAP[k][j] = MAP[k - 1][j];
							if (MAP[k][j] != 0)
							{
								didShift = 1;
								change = 1;
							}
						}
						MAP[0][j] = 0;
						if (change) i++;
					}
				for (int i = N - 1; i>0; i--)
					if (MAP[i][j] == MAP[i - 1][j] && MAP[i][j] != 0)
					{
						didShift = 1;
						for (int k = i; k >= 0; k--)
							MAP[k][j] = MAP[k - 1][j];
						MAP[0][j] = 0;
						MAP[i][j] *= 2;
					}
			}
		}
		else if (d == Direction::Right)
		{
			for (int i = 0; i<N; i++)
			{
				for (int j = M - 1; j >= 0; j--)
					if (MAP[i][j] == 0)
					{
						bool change = 0;
						for (int k = j; k>0; k--)
						{
							MAP[i][k] = MAP[i][k - 1];
							if (MAP[i][k] != 0)
							{
								didShift = 1;
								change = 1;
							}
						}
						MAP[i][0] = 0;
						if (change) j++;
					}
				for (int j = M - 1; j>0; j--)
					if (MAP[i][j] == MAP[i][j - 1] && MAP[i][j] != 0)
					{
						didShift = 1;
						for (int k = j; k>0; k--)
							MAP[i][k] = MAP[i][k - 1];
						MAP[i][0] = 0;
						MAP[i][j] *= 2;
					}
			}
		}
		if (didShift)
			placeNewTile();
	}
	vector<sf::Vector2i> getEmptyCells() {
		vector<sf::Vector2i> empties;
		for (unsigned char ix = 0; ix < 4; ix++) {
			for (unsigned char iy = 0; iy < 4; iy++) {
				if (MAP[ix][iy] == 0) {
					empties.push_back(sf::Vector2i(ix, iy));
				}
			}
		}
		return empties;
	}
	unsigned short getMovesLeft() {
		auto movesLeft = 0;
		for (unsigned char ix = 0; ix < 4; ix++) {
			for (unsigned char iy = 0; iy < 4; iy++) {
				if (MAP[ix][iy] > 0) {
					// If it's a valid tile, look for 0's or the same tile surrounding it as valid moves
					if (ix + 1 < 4 && (MAP[ix][iy] == MAP[ix + 1][iy] || MAP[ix + 1][iy] == 0)) {
						movesLeft++;
					}
					if (iy + 1 < 4 && (MAP[ix][iy] == MAP[ix][iy + 1] || MAP[ix][iy + 1] == 0)) {
						movesLeft++;
					}
				}
			}
		}
		return movesLeft;
	}
	bool isGameOver() {
		if (getEmptyCells().size() > 0 || getMovesLeft() > 0) {
			return false;
		}
		else {
			return true;
		}
		cout << "navay";
	}
	/*if (showGameOver) {
		window.draw(gameOverBackground);
		window.draw(gameOverText);
		scoreDecoratorText.setString("Hit enter to restart");
		scoreDecoratorText.setPosition(sf::Vector2f(gameOverText.getPosition().x + 75, gameOverText.getPosition().y + gameOverText.getLocalBounds().height + padding * 2));
		window.draw(scoreDecoratorText);
	}*/
};


int main()
{
	srand(time(0));
	sf::RenderWindow window(sf::VideoMode(WIDTH - 1, HEIGHT - 1), "beta 2048");
	//window.setVerticalSyncEnabled(true);

	sf::Texture tblank, t2, t4, t8, t16, t32, t64, t128, t256, t512, t1024, t2048, t4096, t8192, tWinner;
	tblank.loadFromFile("blank.png");
	t2.loadFromFile("2.png");
	t4.loadFromFile("4.png");
	t8.loadFromFile("8.png");
	t16.loadFromFile("16.png");
	t32.loadFromFile("32.png");
	t64.loadFromFile("64.png");
	t128.loadFromFile("128.png");
	t256.loadFromFile("256.png");
	t512.loadFromFile("512.png");
	t1024.loadFromFile("1024.png");
	t2048.loadFromFile("2048.png");
	sf::Sprite sprite_blank(tblank);
	sf::Sprite sprite_2(t2);
	sf::Sprite sprite_4(t4);
	sf::Sprite sprite_8(t8);
	sf::Sprite sprite_16(t16);
	sf::Sprite sprite_32(t32);
	sf::Sprite sprite_64(t64);
	sf::Sprite sprite_128(t128);
	sf::Sprite sprite_256(t256);
	sf::Sprite sprite_512(t512);
	sf::Sprite sprite_1024(t1024);
	sf::Sprite sprite_2048(t2048);

	sf::ContextSettings contextSettings;
	contextSettings.depthBits = 24;
	if (!tWinner.loadFromFile("Winner.png"))
		return EXIT_FAILURE;
	sf::Sprite sprite_Winner(tWinner);

	TwoZeroFourEight Game;
	Game.placeNewTile();
	Game.placeNewTile();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed && !g_win)
			{
				if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A)
					Game.shift(Direction::Left);
				else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
					Game.shift(Direction::Right);
				else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
					Game.shift(Direction::Up);
				else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
					Game.shift(Direction::Down);
				else if (event.key.code == sf::Keyboard::R)
					Game.shift(Direction::R);
			}
			else if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		//if (!g_win)
		//	for (int i = 0; i<N; i++)
		//		for (int j = 0; j<M; j++)
		//			if (MAP[i][j] == 2048)
		//			{
		//				//MAP[i][j] = 0;
		//				//sprite_Winner.setPosition(j*TILESIZE, i*TILESIZE);
		//				window.draw(sprite_Winner);
		//				g_win = 1;
		//			}
						
		if (!showGameOver) {
			if(Game.isGameOver()==true){
				cout << "navay\n";
			}
			else {
				cout << "nonavay\n";
			}
		}
		for (int i = 0; i<M; i++)
			for (int j = 0; j<N; j++)
			{
				if (MAP[i][j] == 0)
				{
					sprite_blank.setPosition(j*TILESIZE, i*TILESIZE);
					window.draw(sprite_blank);
				}
				else if (MAP[i][j] == 2)
				{
					sprite_2.setPosition(j*TILESIZE, i*TILESIZE);
					window.draw(sprite_2);
				}
				else if (MAP[i][j] == 4)
				{
					sprite_4.setPosition(j*TILESIZE, i*TILESIZE);
					window.draw(sprite_4);
				}
				else if (MAP[i][j] == 8)
				{
					sprite_8.setPosition(j*TILESIZE, i*TILESIZE);
					window.draw(sprite_8);
				}
				else if (MAP[i][j] == 16)
				{
					sprite_16.setPosition(j*TILESIZE, i*TILESIZE);
					window.draw(sprite_16);
				}
				else if (MAP[i][j] == 32)
				{
					sprite_32.setPosition(j*TILESIZE, i*TILESIZE);
					window.draw(sprite_32);
				}
				else if (MAP[i][j] == 64)
				{
					sprite_64.setPosition(j*TILESIZE, i*TILESIZE);
					window.draw(sprite_64);
				}
				else if (MAP[i][j] == 128)
				{
					sprite_128.setPosition(j*TILESIZE, i*TILESIZE);
					window.draw(sprite_128);
				}
				else if (MAP[i][j] == 256)
				{
					sprite_256.setPosition(j*TILESIZE, i*TILESIZE);
					window.draw(sprite_256);
				}
				else if (MAP[i][j] == 512)
				{
					sprite_512.setPosition(j*TILESIZE, i*TILESIZE);
					window.draw(sprite_512);
				}
				else if (MAP[i][j] == 1024)
				{
					sprite_1024.setPosition(j*TILESIZE, i*TILESIZE);
					window.draw(sprite_1024);
				}
				else if (MAP[i][j] == 2048)
				{
					sprite_2048.setPosition(j*TILESIZE, i*TILESIZE);
					window.draw(sprite_2048);
					//sprite_Winner.setPosition(j*TILESIZE, i*TILESIZE);
					//window.draw(sprite_Winner);
					/*for (int i = 0; i < M; i++)
						for (int j = 0; j < N; j++)
							MAP[i][j] = NULL;*/
					//window.clear();
					//window.draw(sprite_2048);
					//window.pushGLStates();
					//EXIT_FAILURE;
					//window.popGLStates();
					//window.setActive(true);
				}
				/*else if (MAP[i][j] >= 2048) {
				}*/
			}
		window.display();
	}


}
