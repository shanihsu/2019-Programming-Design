#include <math.h>
using namespace std;
class score{
	public:
		void set(float Ra, float Rb, int K);
		void calculate(float Sa, float Ra_p, float Rb_p, int K_p);
		float getRa();
		float getRb();
	private:
		int K_p;
		float Ra_p, Rb_p, Ra_pc, Rb_pc;
};
