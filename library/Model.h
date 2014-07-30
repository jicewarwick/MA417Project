#ifndef MODEL_H_2YIGZRLQ
#define MODEL_H_2YIGZRLQ

class Model {
public:
	Model(){}
	virtual ~Model (){}
	virtual double* PathFactory() = 0;
	virtual double get_ST() = 0;
	virtual double get_path_mean() = 0;
	virtual int get_dim() = 0;

private:

};

#endif /* end of include guard: MODEL_H_2YIGZRLQ */

