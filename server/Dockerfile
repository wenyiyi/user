FROM ubuntu

ADD . /user_server
WORKDIR /user_server

RUN set -e; \
  apt-get update; \
  apt-get install -y curl gnupg; \
  echo "deb [arch=amd64] https://storage.googleapis.com/bazel-apt stable jdk1.8" | tee /etc/apt/sources.list.d/bazel.list \
  curl https://bazel.build/bazel-release.pub.gpg | apt-key add -; \
  apt-get update; \
  apt-get install -y bazel; \
  apt-get install --only-upgrade -y bazel; \
  bazel build //src:user_server; \
  apt-get update; \
  apt-get install build-essential;

