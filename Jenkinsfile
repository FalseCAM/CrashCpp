node {
  stage 'Checkout'
   checkout scm
   sh 'git submodule update --init --recursive'

  stage 'Build'
   sh 'mkdir -p build'
   sh 'cd build && cmake -DOPTION_BUILD_DOCS=1 .. && make && make pack'

  stage 'Package'
   sh 'cd build && make pack'

}
