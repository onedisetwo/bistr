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
		err_type state = err_type::success;
	public:
		Status () = default;
		Status (const err_type& n_state) {
			state = n_state;
		}
		bool good () {
			return (state == err_type::success ? true : false);
		}
		void print_error_message () {
			if(state == err_type::success)
				return ;
		}
		int operator!= (const Status& n_st) {
			return (state != n_st.state ? 1 : 0);
		}
} ;

# endif //STATUS
