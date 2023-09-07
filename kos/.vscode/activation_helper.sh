# Check if ~/.bashrc exists and source it
if [ -f ~/.bashrc ]; then
    source ~/.bashrc
fi
source ../activate-toolchains.sh