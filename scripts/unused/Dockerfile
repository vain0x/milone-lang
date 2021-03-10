# <https://hub.docker.com/_/microsoft-dotnet-sdk>
FROM mcr.microsoft.com/dotnet/sdk:5.0

# <https://docs.microsoft.com/en-us/dotnet/core/tools/dotnet#environment-variables>
ENV DOTNET_CLI_TELEMETRY_OPTOUT=1 \
    DOTNET_NOLOGO=1 \
    PATH=$PATH:$HOME/bin

RUN apt-get update && \
    apt-get install -y \
        gcc \
        git \
        ninja-build \
        && \
    apt-get clean

WORKDIR /usr/local/src/milone-lang

COPY . ./

RUN ./install && \
    ./clean

ENTRYPOINT [ "milone" ]
