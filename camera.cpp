#include "triangle.h"
#include "globals.h"

using namespace::std;

void InitCamera() {
	matrix m_T = matrix();
	matrix m_B = matrix();
	m_T.init_m_t(ViewPoint);
	m_B.init_m_b(N,V,U);
	m_E = m_T.mult(m_B);
}

void World2View() {
	vector<triangle>::iterator it = trangles.begin();
	for (;it!=trangles.end();it++) {
		it->A.v.extend(1);
		it->B.v.extend(1);
		it->C.v.extend(1);

		it->A.v=it->A.v.mult(m_E);
		it->B.v=it->B.v.mult(m_E);
		it->C.v=it->C.v.mult(m_E);

		//printf("%lf,%lf,%lf\n", it->A.x, it->A.y, it->A.z);
	}
}

void View2Screen() {
	
	m_V2S.init_m_v2s(A,B,with_A,with_B,high_A,high_B);

	vector<triangle>::iterator it = trangles.begin();
	for (; it != trangles.end(); it++) {
		it->A.v = m_V2S.mult(it->A.v);
		it->B.v = m_V2S.mult(it->B.v);
		it->C.v = m_V2S.mult(it->C.v);

		it->A.v.cut();
		it->B.v.cut();
		it->C.v.cut();

		//·ÅËõµ½ÆÁÄ»
		it->A.v.x = (it->A.v.x) * 300 + 300;
		it->B.v.x = (it->B.v.x) * 300 + 300;
		it->C.v.x = (it->C.v.x) * 300 + 300;
		it->A.v.y = (it->A.v.y) * -300 + 300;
		it->B.v.y = (it->B.v.y) * -300 + 300;
		it->C.v.y = (it->C.v.y) * -300 + 300;
		//it->A.v.z = (it->A.v.z) * 300 + 300;
		//it->B.v.z = (it->B.v.z) * 300 + 300;
		//it->C.v.z = (it->C.v.z) * 300 + 300;
		
		//printf("%lf,%lf,%lf\n", it->A.x, it->A.y, it->A.z);
	}
	//triangle showT = 
}