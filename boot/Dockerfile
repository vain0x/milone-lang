FROM mcr.microsoft.com/dotnet/core/sdk:3.1

ENV DOTNET_SKIP_FIRST_TIME_EXPERIENCE=1
ENV DOTNET_CLI_TELEMETRY_OPTOUT=1

RUN apt-get update
RUN apt-get install -y gcc

WORKDIR /mnt/milone-lang/boot
