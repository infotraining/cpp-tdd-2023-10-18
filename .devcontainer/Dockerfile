FROM gcc:latest

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
     && apt-get -y install --no-install-recommends cmake curl zip unzip tar 
     # && apt-get -y install --no-install-recommends libboost-all-dev

RUN git clone https://github.com/Microsoft/vcpkg.git /opt/vcpkg

WORKDIR /opt/vcpkg

RUN ./bootstrap-vcpkg.sh && ./vcpkg integrate install && ./vcpkg integrate bash && echo 'export PATH=$PATH:/opt/vcpkg' >>~/.bashrc
RUN echo 'export VCPKG_ROOT=/opt/vcpkg' >>~/.bashrc

# RUN /opt/vcpkg/vcpkg install catch2 gtest bext-di

WORKDIR /root