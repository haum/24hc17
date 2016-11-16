#include "game__AveCaesar.h"
#include "EncodedState.h"

namespace game {
namespace AveCaesar {
	void init_data(void * data) {
		Data * d = static_cast <Data*> (data);
		d->faults = 0;
	}

	bool play(void * data, GameManager::GameInfo & info) {
		const char msg[] = "AVE IMPERATOR, NVNTIVS VENIT.\n\n"
		"Gvzr unf pbzr gb cebir lbhe jbegu. Va gur arkg 24u (be yrff) lbh jvyy unir gb nafjre\n"
"dhrfgvbaf, fbyir ceboyrzf, ravtznf naq znlor zbir lbhe nff bhg bs lbhe punve.\n"
"Areb jvyy fgnl ol lbhe fvqr nf gur tbbq zragbe ur vf. Cyrnfr xrrc fraqvat uvz lbhe\n"
"thrffrf, ur funyy gura tvir lbh gur xrlf gb zbir sbejneq.\n\n"

"Areb vf snve ohg ungrf ybbfref. Rnpu gvzr lbh snvy, lbhe punapr bs orvat chavfurq vapernfrf.\n\n"

"Cebir lbh'ir qrpbqrq guvf zrffntr naq fnl nir gb gur Ynhzvb.\n";
	  info.comm.write(msg, sizeof(msg));

    Data * d = static_cast <Data*> (data);
		char ans[255];
		int len = info.comm.read(ans, sizeof(ans));
		if (len == 3 && ans[0] == 'a' && ans[1] == 'v' && ans[2] == 'e') {
			EncodedState newstate;
			newstate.faults() = d->faults;
			newstate.riddle() = info.state.riddle() + 1;
			char token[22];
			newstate.toString(token);
			info.comm.write("\nAve! Here is the next message to Nero:\n", 40);
			info.comm.write(token, sizeof(token));
			info.comm.write("\n", 1);
			return true;
		} else {
		  d->faults++;
		}
		return false;
	}
}
}
