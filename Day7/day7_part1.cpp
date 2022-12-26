#include "stdafx.h"

// #define TEST_DATA 1

namespace day_7_part_1
{
	struct file
	{
		std::string name;
		int size;
	};

	class directory
	{
	public:
		int get_size() const
		{
			int total_size = 0;

			for ( auto file : files )
			{
				total_size += file.size;
			}

			for ( auto dir : directories )
			{
				total_size += dir.get_size();
			}

			return total_size;
		}

		void display( int level )
		{
			for ( int i = 0; i < level; ++i )
				std::cout << '\t';

			std::cout << name << " (dir)" << std::endl;

			for ( auto dir : directories )
			{
				dir.display( level + 1 );
			}

			for ( auto file : files )
			{
				for ( int i = 0; i <= level; ++i )
				{
					std::cout << '\t';
				}
				std::cout << file.name << " (file, size=" << file.size << ")" << std::endl;
			}
		}

		void start_record_inside()
		{
			record = true;
		}

		void stop_record_inside()
		{
			record = false;
		}

		void add_directory( std::string dir_name )
		{
			if ( !record )
			{
				return;
			}

			directory new_dir;
			new_dir.name = dir_name;
			new_dir.parent = this;
			directories.push_back( new_dir );
		}

		void add_file( std::string line )
		{
			if ( !record )
			{
				return;
			}

			size_t pos_space = line.find_first_of( ' ' );

			std::string file_size = line.substr( 0, pos_space );
			std::string file_name = line.substr( pos_space + 1 );

			file new_file;
			new_file.size = atoi( file_size.c_str() );
			new_file.name = file_name;
			files.push_back( new_file );
		}

		directory* move( std::string dir_name )
		{
			if ( dir_name == ".." )
			{
				if ( parent )
				{
					return parent;
				}
				else
				{
					return this;
				}
			}

			for ( auto& dir : directories )
			{
				if ( dir.name == dir_name )
				{
					return &dir;
				}
			}
			return this;
		}

		void set_name( std::string new_name )
		{
			name = new_name;
		}

		const std::vector< directory >& get_directories() const
		{
			return directories;
		}

	private:
		std::vector< directory > directories;
		std::vector< file > files;
		directory* parent = nullptr;
		std::string name;
		bool record = false;
	};

	struct data
	{
		directory root;

		void get_all_sizes( const directory& current, int mini, int& total_size ) const
		{
			for ( auto dir : current.get_directories() )
			{
				get_all_sizes( dir, mini, total_size );

				auto size = dir.get_size();
				if ( size <= mini )
				{
					total_size += size;
				}
			}
		}

		void output_all_dir_size_more_than( int mini )
		{
			int total_size = 0;
			get_all_sizes( root, mini, total_size );
			std::cout << "Total size: " << total_size << std::endl;
		}

	};

	const std::vector< std::string > load_inputs()
	{
#ifdef TEST_DATA
		const std::vector< std::string > test_inputs =
		{
			"$ cd /",
			"$ ls",
			"dir a",
			"14848514 b.txt",
			"8504156 c.dat",
			"dir d",
			"$ cd a",
			"$ ls",
			"dir e",
			"29116 f",
			"2557 g",
			"62596 h.lst",
			"$ cd e",
			"$ ls",
			"584 i",
			"$ cd ..",
			"$ cd ..",
			"$ cd d",
			"$ ls",
			"4060174 j",
			"8033020 d.log",
			"5626152 d.ext",
			"7214296 k"
		};
		return test_inputs;
#else
		std::vector< std::string > real_inputs;

		FILE* real_inputs_file;
		auto result = fopen_s( &real_inputs_file, "data/day7/input.txt", "r" );

		if ( result == 0 )
		{
			char buffer[ 128 ];
			char* read = fgets( buffer, 128, real_inputs_file );
			while ( read )
			{
				std::string line( read );
				line = line.substr( 0, line.size() - 1 ); // remove /n
				real_inputs.push_back( line );
				read = fgets( buffer, 128, real_inputs_file );
			}
			fclose( real_inputs_file ); // ALWAYS CLOSE AN OPENED FILE
		}
		return real_inputs;
#endif
	}

	void process( const std::vector< std::string >& inputs, data& data )
	{
		data.root.set_name( "/" );
		directory* current_dir = &data.root;

		for ( auto line : inputs )
		{
			if ( line[ 0 ] == '$' )
			{
				current_dir->stop_record_inside();
			}

			if ( line.find( "$ cd " ) != std::string::npos )
			{
				current_dir = current_dir->move( line.substr( 5 ) );
			}
			else if ( line.find( "$ ls" ) != std::string::npos )
			{
				current_dir->start_record_inside();
			}
			else if ( line.find( "dir " ) != std::string::npos )
			{
				current_dir->add_directory( line.substr( 4 ) );
			}
			else
			{
				current_dir->add_file( line );
			}
		}
	}

	void display_result( data& data )
	{
		std::cout << "Day 7 : Part 1" << std::endl;
		data.output_all_dir_size_more_than( 100000 );
		std::cout << std::endl;
	}
}

void day_7_run_part_1()
{
	day_7_part_1::data data;

	day_7_part_1::process( day_7_part_1::load_inputs(), data );
	day_7_part_1::display_result( data );
}