
export BOOST_ROOT=/usr/boost_1_47_0
export SOLUTION_NAME=task2

export BUILD_TYPE=Debug
if ( "$1" == 'Release' );
then
	export BUILD_TYPE=Release
fi

export BUILD_FOLDER=_build_"$BUILD_TYPE"_32

if ( ! -d $BUILD_FOLDER );
then
	mkdir $BUILD_FOLDER
fi

cd $BUILD_FOLDER
cmake -DVERBOSE=ON -DSOLUTION_NAME=$SOLUTION_NAME -DCMAKE_BUILD_TYPE=$BUILD_TYPE -G "CodeBlocks - Unix Makefiles" ../ 
cd ../

