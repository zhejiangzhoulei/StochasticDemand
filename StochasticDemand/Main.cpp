#include"Util.h"

#include"Schedule.h"
#include"IO.h"
#include"Model.h"
int main()
{
	Schedule* sche = new Schedule();

	IO* io = new IO();
	io->input(sche);

	Model* model = new Model(sche);
	model->solve();



	return 0;
}