# ifndef STATUS
# define STATUS

enum class err_type {
	success,
	eof,
	open,
	format,
	memory,
	unknown,
} ;

class Status {
	private:
		state e = err_type::success;
	public:
		Status (const err_type& n_e) {
			e = n_e.state;
		}
		bool good () {
			return (e == err_type::success ? true : false)
		}
		void print_error_message () {
			if(e == err_type::success)
				return ;
		}
}

# endif STATUS
