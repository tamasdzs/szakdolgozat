#ifndef __OPTIMIZER_H__
#define __OPTIMIZER_H__

#include <limits>
#include <vector>
#include <functional>


/* 
 *	STRUCT: Coord 
 * 	This struct defines the coordinate of a given particle.
 * 	These coordinates will be used to locate particles in the search
 * 	space for optimization algorithms. (Nelder-Mead, PSO, steepest descent)
*/
struct Coord{
	double l;
	double t;
	Coord(): l(0.0), t(0.0) {}
	Coord operator+(const Coord a){
		Coord ans;
		ans.l = this->l + a.l;
		ans.t = this->t + a.t;
		return ans;
	}
	Coord operator-(const Coord a){
		Coord ans;
		ans.l = this->l - a.l;
		ans.t = this->t - a.t;
		return ans;
	}
	Coord operator*(const double a){
		Coord ans;
		ans.l = this->l*a;
		ans.t = this->t*a;
		return ans;
	}
	Coord operator/(const double a){
		
		Coord ans;
		ans.l = this->l/a;
		ans.t = this->t/a;
		return ans;
	}
	void operator=(const Coord a) {
		this->l = a.l;
		this->t = a.t;
	}
};

/*
 *	STRUCT: Particle 
 * 	This struct defines a particle, which are used by the optimization
 * 	algorithms. 
*/

/*
struct Particle{
	double PRD;
	double velocity;
	Coord location;
	Eigen::MatrixXd co; 
	Particle(): PRD(std::numeric_limits<double>::max()), velocity(0.0) {}
};
*/

/*
 *  CLASS: Optimizer:
 * 	Parent class of all optimization classes. Pure virtual function optimize 
 * 	is responsible of the execution of the desired optimization algorithm.
 * 	It returns a Coord, and takes as a parameter an anonymus function.
 *  The class also includes protected member generations, which determines the 
 * 	number of times the optimization algorithm runs. In addition the maximum error 
 * 	can be given.
*/

class Optimizer {
	protected:
		const unsigned int generations;
		const double max_err;
	public:
		Optimizer( const unsigned int gen, const double merr ) : generations(gen), max_err(merr) {}
		~Optimizer() {}
		virtual Coord Optimize( std::function<double (Coord &)> costfun ) = 0;
};

#endif