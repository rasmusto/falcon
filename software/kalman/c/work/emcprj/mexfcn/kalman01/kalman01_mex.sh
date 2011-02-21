MATLAB="/Applications/MATLAB_R2010b.app"
Arch=maci64
ENTRYPOINT=mexFunction
MAPFILE=$ENTRYPOINT'.map'
PREFDIR="/Users/cooleys/.matlab/R2010b"
OPTSFILE_NAME=mexopts.sh
. $OPTSFILE_NAME
COMPILER=$CC
. $OPTSFILE_NAME
echo "# Make settings for kalman01" > kalman01_mex.mki
echo "CC=$CC" >> kalman01_mex.mki
echo "CFLAGS=$CFLAGS" >> kalman01_mex.mki
echo "CLIBS=$CLIBS" >> kalman01_mex.mki
echo "COPTIMFLAGS=$COPTIMFLAGS" >> kalman01_mex.mki
echo "CDEBUGFLAGS=$CDEBUGFLAGS" >> kalman01_mex.mki
echo "CXX=$CXX" >> kalman01_mex.mki
echo "CXXFLAGS=$CXXFLAGS" >> kalman01_mex.mki
echo "CXXLIBS=$CXXLIBS" >> kalman01_mex.mki
echo "CXXOPTIMFLAGS=$CXXOPTIMFLAGS" >> kalman01_mex.mki
echo "CXXDEBUGFLAGS=$CXXDEBUGFLAGS" >> kalman01_mex.mki
echo "LD=$LD" >> kalman01_mex.mki
echo "LDFLAGS=$LDFLAGS" >> kalman01_mex.mki
echo "LDOPTIMFLAGS=$LDOPTIMFLAGS" >> kalman01_mex.mki
echo "LDDEBUGFLAGS=$LDDEBUGFLAGS" >> kalman01_mex.mki
echo "Arch=$Arch" >> kalman01_mex.mki
echo OMPFLAGS= >> kalman01_mex.mki
echo OMPLINKFLAGS= >> kalman01_mex.mki
echo "EMC_COMPILER=unix" >> kalman01_mex.mki
echo "EMC_CONFIG=optim" >> kalman01_mex.mki
"/Applications/MATLAB_R2010b.app/bin/maci64/gmake" -B -f kalman01_mex.mk
