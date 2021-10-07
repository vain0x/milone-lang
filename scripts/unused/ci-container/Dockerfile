FROM mcr.microsoft.com/dotnet/sdk:5.0-focal

ENV DOTNET_CLI_TELEMETRY_OPTOUT=true \
    DOTNET_NOLOGO=true

# sed enables mirrors for apt-get update.
# sed -i.orig -r 's;(deb|deb-src) \S+;\1 mirror://mirrors.ubuntu.com/mirrors.txt;' /etc/apt/sources.list
# (not worked for some reason)

RUN apt-get update && \
    apt-get install -y \
        busybox-static \
        gcc \
        git \
        inotify-tools \
        make \
        && \
    apt-get clean

COPY docker-entrypoint \
    docker-init \
    on-build \
    on-build-wrap \
    on-error \
    /etc/

CMD [ "sh", "/etc/docker-entrypoint" ]
