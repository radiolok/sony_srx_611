# Build a self-contained SRX-C61 emulator container.
#
#   cd emu && ./make_roms.sh && docker build -t srx-c61-emu .
#
# The image is built from a pinned MAME release and contains only the srx_c61
# driver (built with SOURCES= for a fast, small build) plus the firmware ROMs.

# ---- build stage -----------------------------------------------------------
FROM ubuntu:22.04 AS build

RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential \
        git \
        python3 \
        ca-certificates \
        libsdl2-dev \
        libsdl2-ttf-dev \
        libfontconfig1-dev \
    && rm -rf /var/lib/apt/lists/*

ARG MAME_VERSION=mame0289
ARG MAKE_JOBS

RUN git clone --depth 1 --branch "${MAME_VERSION}" https://github.com/mamedev/mame.git /src/mame

# Install the SRX-C61 driver and register it in the driver list.
COPY src/mame/sony/srx_c61.cpp /src/mame/src/mame/sony/srx_c61.cpp
RUN sed -i '/^@source:sony\/taitogn\.cpp$/i @source:sony/srx_c61.cpp\nsrx_c61\n' /src/mame/src/mame/mame.lst

WORKDIR /src/mame
RUN make -j"${MAKE_JOBS:-$(nproc)}" \
        SOURCES=src/mame/sony/srx_c61.cpp \
        REGENIE=1 \
        USE_QTDEBUG=0 \
        NO_USE_MIDI=1 NO_USE_PORTAUDIO=1 NO_USE_PULSEAUDIO=1 NO_USE_PIPEWIRE=1

# ---- runtime stage ----------------------------------------------------------
FROM ubuntu:22.04

RUN apt-get update && apt-get install -y --no-install-recommends \
        libsdl2-2.0-0 \
        libsdl2-ttf-2.0-0 \
        libgl1 \
        libflac8 \
        libfontconfig1 \
        libglib2.0-0 \
        libsndfile1 \
    && rm -rf /var/lib/apt/lists/*

COPY --from=build /src/mame/mame /usr/local/bin/srx-c61
COPY roms /roms
COPY docker-entrypoint.sh /usr/local/bin/docker-entrypoint.sh

# Headless by default: no X11/audio, SDL falls back to the dummy driver.
ENV SDL_VIDEODRIVER=dummy \
    SDL_AUDIODRIVER=dummy \
    XDG_RUNTIME_DIR=/tmp

WORKDIR /roms

ENTRYPOINT ["docker-entrypoint.sh"]
CMD ["srx_c61", "-video", "none", "-sound", "none", "-nothrottle"]
