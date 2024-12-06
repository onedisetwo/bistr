# ifndef GEOMETRY
# define GEOMETRY

# include <cmath>
# include <cstdio>
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
			Status read (FILE* fp = stdin, bool is_human = true) {
				if(fp == nullptr)
					return Status(err_type::open);
				if(is_human)  printf("Input coordinates: ");
				if(fscanf(fp, "%lf %lf", &x, &y) != 2)
					return Status(err_type::format);
				return Status(err_type::success);
			}
			void print () {
				printf("x: %lf , y: %lf\n", x, y);
			}
			double get_distance (Point& p) const {
				return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
			}
			friend class Polygon;
	} ;

	class Vector {
		private:
			double x = 0;
			double y = 0;
		public:
			Vector () = default;
			Vector (double n_x, double n_y) {
				x = n_x;  y = n_y;
			}
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
//			void print()
			double length () const {
				return sqrt(x*x + y*y);
			}
			double get_angle () const {
				return (x != 0 ? atan(y / x) : (y > 0 ? M_PI/2. : -M_PI/2.));
			}
	} ;

	class Polygon {
		private:
			int n = 0;
			Point* vertex = nullptr;
		public:
			Polygon () = default;
			Polygon (int n_n) {
				n = n_n;
				vertex = new Point[n];
			}
			~Polygon () {
				delete[] vertex;
			}
			Status read (FILE *fp = stdin, bool is_human = true) {
				if(fp == nullptr)
					return Status(err_type::open);
				if(is_human)  printf("Enter number of vertices: ");
				if(fscanf(fp, "%d", &n) != 1)
					return Status(err_type::format);
				vertex = new Point[n];
				if(is_human)  printf("Enter vertices' coordinates:\n");
				for(int i = 0; i < n; i++){
					if(!vertex[i].read(fp, is_human).good())
						return Status(err_type::format);
				}
				return Status(err_type::success);
			}
			void print () {
				printf("Number of vertices: %d\n", n);
				for(int i = 0; i < n; i++)
					printf("%d: %lf %lf\n", i + 1, vertex[i].x, vertex[i].y);
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
			double get_view_angle (Point& p) {
				double min_angle = M_PI, max_angle = -M_PI, tmp;
				for(int i = 0; i < n; i++) {
					Vector v(vertex[i].x - p.x, vertex[i].y - p.y);
					tmp = v.get_angle();
					printf("%lf\n", tmp);
					min_angle = std::min(min_angle, tmp);
					max_angle = std::max(max_angle, tmp);
				}
				return max_angle - min_angle;
			}
	} ;

}

# endif // GEOMETRY
