# ifndef GEOMETRY
# define GEOMETRY

# include <cmath>
# include "status.h"

namespace R2 {

	class Point {
		private:
			double x = 0;
			double y = 0;
		public:
			Point () = default;
			~Point () = default;
			// void init (double n_x, double n_y) {
			// 	x = n_x;  y = n_y;
			// }
			Point (const Point& p) {
				x = p.x;  y = p.y;
			}
			Point& operator= (const Point& p) {
				x = p.x;  y = p.y;
				return *this;
			}
			// file must be opened before function
			Status read (FILE* fp = stdin) {
				if(fp == nullptr)
					return Status(err_type::open);
				if(fscanf(fp, "%lf %lf", x, y) != 2)
					return Status(err_type::format);
				return Status(err_type::success);
			}
			double get_distance (Point& p) const {
				return sqrt(pow(x - x.p, 2) + pow(y - y.p, 2));
			}
	}

	class Vector {
		private:
			double x = 0;
			double y = 0;
		public:
			Vector () = default;
			~Vector () = default;
			void init (double n_x, double n_y) {
				x = n_x;  y = n_y;
			}
			Vector (const Vector& v) {
				x = v.x;  y = v.y;
			}
			Vector& operator= (const Vector& v) {
				x = v.x;  y = v.y;
				return *this;
			}
			void print()
			double length () const {
				return sqrt(x*x + y*y);
			}
			double get_angle (const Vector& v) const {
				return (x != 0 ? arctan(y / x) : (y > 0 ? 0.5 : -0.5));
			}
	}

	class Polygon {
		private:
			int n = 0;
			Point* vertex = nullptr;
		public:
			Polygon () = default;
			Polygon (int n) {
				vertex = new Point[n];
			}
			~Polygon () {
				delete[] vertex;
			}
			bool good () const {
				if(n != 0 && vertex == nullptr)
					return false;
				else
					return true;
			}
			Point* get_k_vertex (int k) {
				if(k >= 0 && k <= n)
					return vertex + k;
				else
					return nullptr;
			}
	}

}

# endif // GEOMETRY
