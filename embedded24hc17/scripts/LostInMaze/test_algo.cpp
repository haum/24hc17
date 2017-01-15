#include <stdio.h>
#include <string.h>

class Map {
	static constexpr int W {17};
	static constexpr int H {15};
	char map[H][W];
public:
	Map() {
		constexpr const char * strmap = "#################"
		                                "#............#..#"
		                                "#.#######..#.#..#"
		                                "#.#.....##.#....."
		                                "#.#.###....#.#..#"
		                                "#.###.######.#..#"
		                                "#............#..#"
		                                "#.###.####.#.#..#"
		                                "#.#.#.#..#.#.#..#"
		                                "#.#.#.##.###.#..#"
		                                "#...............#"
		                                "##############.##"
		                                "#....#..........#"
		                                "#.........#.....#"
		                                "#################";
		int i = 0;
		for (auto & l : map)
			for (auto & c : l)
				c = strmap[i++];
	}

	void print(void(*print)(char)) {
		for (auto & l : map) {
			for (auto c : l) {
				print(c);
			}
			print('\n');
		}
	}

	void go(char dir) {
		char newmap[H][W];
		memcpy(newmap, map, sizeof(newmap));
		switch(dir) {
			case 'n':
				for (int i = 1; i < H-1; ++i) {
					for (int j = 0; j < W; ++j) {
						if (map[i][j] == '.') {
							if (map[i-1][j] != '#' && map[i+1][j] != '.')
								newmap[i][j] = ' ';
						}
						if (map[i][j] == ' ') {
							if (map[i+1][j] == '.')
								newmap[i][j] = '.';
						}
					}
				}
				break;
			case 's':
				for (int i = 1; i < H-1; ++i) {
					for (int j = 0; j < W; ++j) {
						if (map[i][j] == '.') {
							if (map[i+1][j] != '#' && map[i-1][j] != '.')
								newmap[i][j] = ' ';
						}
						if (map[i][j] == ' ') {
							if (map[i-1][j] == '.')
								newmap[i][j] = '.';
						}
					}
				}
				break;
			case 'w':
				for (int i = 0; i < H; ++i) {
					for (int j = 1; j < W-1; ++j) {
						if (map[i][j] == '.') {
							if (map[i][j-1] != '#' && map[i][j+1] != '.')
								newmap[i][j] = ' ';
						}
						if (map[i][j] == ' ') {
							if (map[i][j+1] == '.')
								newmap[i][j] = '.';
						}
					}
					if (map[3][16] == '.') {
						newmap[3][16] = ' ';
					}
				}
				break;
			case 'e':
				for (int i = 0; i < H; ++i) {
					for (int j = 1; j < W-1; ++j) {
						if (map[i][j] == '.') {
							if (map[i][j+1] != '#' && map[i][j-1] != '.')
								newmap[i][j] = ' ';
						}
						if (map[i][j] == ' ') {
							if (map[i][j-1] == '.')
								newmap[i][j] = '.';
						}
					}
					if (map[3][16] == '.') {
						if (map[3][15] != '.')
							newmap[3][16] = ' ';
					}
					if (map[3][16] == ' ') {
						if (map[3][15] == '.')
							newmap[3][16] = '.';
					}
				}
				break;
		}
		memcpy(map, newmap, sizeof(map));
	}
};

int main() {
	Map map;
	int c;
	while((c = getchar()) != -1) {
		map.go(c);
		if (c != '\n')
			map.print([](char c){ printf("%c", c); });
	}

	return 0;
}
