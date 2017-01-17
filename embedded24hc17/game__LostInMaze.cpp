#include "game__LostInMaze.h"
#include "EncodedState.h"
#include <cstring>
#include <FS.h>

namespace game {
namespace LostInMaze {
	void init_data(void * data) {
		Data * d = static_cast <Data*> (data);
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
		for (auto & l : d->map)
			for (auto & c : l)
				c = strmap[i++];
	}

	void print(Data * d, GameManager::GameInfo & info) {
		for (auto & l : d->map) {
			for (auto c : l) {
				info.comm.write(&c, 1);
			}
			char c = '\n';
			info.comm.write(&c, 1);
		}
	}

	bool play(void * data, GameManager::GameInfo & info) {
		Data * d = static_cast <Data*> (data);
		char file[255];

		// Prelude
		snprintf(file, sizeof(file), "/LostInMaze/prelude");
		info.comm.dump_file(file);

		// Process
		char ans_line[255];
		int ans_line_len = info.comm.read(ans_line, sizeof(ans_line));
		for (int oo = 0; oo < ans_line_len; ++oo) {
			char newmap[H][W];
			memcpy(newmap, d->map, sizeof(newmap));
			switch(ans_line[oo]) {
				case 'n':
					for (int i = 1; i < H-1; ++i) {
						for (int j = 0; j < W; ++j) {
							if (d->map[i][j] == '.') {
								if (d->map[i-1][j] != '#' && d->map[i+1][j] != '.')
									newmap[i][j] = ' ';
							}
							if (d->map[i][j] == ' ') {
								if (d->map[i+1][j] == '.')
									newmap[i][j] = '.';
							}
						}
					}
					break;
				case 's':
					for (int i = 1; i < H-1; ++i) {
						for (int j = 0; j < W; ++j) {
							if (d->map[i][j] == '.') {
								if (d->map[i+1][j] != '#' && d->map[i-1][j] != '.')
									newmap[i][j] = ' ';
							}
							if (d->map[i][j] == ' ') {
								if (d->map[i-1][j] == '.')
									newmap[i][j] = '.';
							}
						}
					}
					break;
				case 'w':
					for (int i = 0; i < H; ++i) {
						for (int j = 1; j < W-1; ++j) {
							if (d->map[i][j] == '.') {
								if (d->map[i][j-1] != '#' && d->map[i][j+1] != '.')
									newmap[i][j] = ' ';
							}
							if (d->map[i][j] == ' ') {
								if (d->map[i][j+1] == '.')
									newmap[i][j] = '.';
							}
						}
						if (d->map[3][16] == '.') {
							newmap[3][16] = ' ';
						}
					}
					break;
				case 'e':
					for (int i = 0; i < H; ++i) {
						for (int j = 1; j < W-1; ++j) {
							if (d->map[i][j] == '.') {
								if (d->map[i][j+1] != '#' && d->map[i][j-1] != '.')
									newmap[i][j] = ' ';
							}
							if (d->map[i][j] == ' ') {
								if (d->map[i][j-1] == '.')
									newmap[i][j] = '.';
							}
						}
						if (d->map[3][16] == '.') {
							if (d->map[3][15] != '.')
								newmap[3][16] = ' ';
						}
						if (d->map[3][16] == ' ') {
							if (d->map[3][15] == '.')
								newmap[3][16] = '.';
						}
					}
					break;
			}
			memcpy(d->map, newmap, sizeof(d->map));
			//print(d, info);
		}

		// count faults
		int fault = 0;
		for (auto & l : d->map) {
			for (auto c : l) {
				if (c == '.')
					fault++;
			}
		}
		if (fault >= 16)
			fault = 15;

		// Write token
		EncodedState newstate = info.state;
		newstate.faults() = fault;
		newstate.finalsuccess() = 1;
		newstate.direction() = 1;
		char token[22];
		newstate.toString(token);
		info.comm.write("\nToken: ", 8);
		info.comm.write(token, sizeof(token));
		info.comm.write("\n", 1);
		return true;
	}
}
}
