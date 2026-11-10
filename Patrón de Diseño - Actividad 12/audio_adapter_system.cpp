#include <iostream>
#include <string>
#include <memory>


// 1. Interfaz Target (Objetivo)

class ReproductorAudio {
public:
    virtual ~ReproductorAudio() = default;
    virtual void reproducir(const std::string& tipoArchivo, const std::string& nombreArchivo) = 0;
};


// 2. Adaptee (Sistema de Audio Incompatible)

class ReproductorAvanzado {
public:
    void reproducirVlc(const std::string& nombreArchivo) {
        std::cout << "[VLC Player] Procesando y reproduciendo: " << nombreArchivo << std::endl;
    }

    void reproducirMp4(const std::string& nombreArchivo) {
        std::cout << "[MP4 Player] Decodificando y reproduciendo: " << nombreArchivo << std::endl;
    }
};


// 3. Adapter (Adaptador de Interfaces)

class AdaptadorAudio : public ReproductorAudio {
private:
    // Encapsulamiento del componente adaptado mediante un puntero inteligente
    std::unique_ptr<ReproductorAvanzado> reproductorAvanzado;

public:
    AdaptadorAudio() : reproductorAvanzado(std::make_unique<ReproductorAvanzado>()) {}

    void reproducir(const std::string& tipoArchivo, const std::string& nombreArchivo) override {
        if (tipoArchivo == "vlc") {
            reproductorAvanzado->reproducirVlc(nombreArchivo);
        } else if (tipoArchivo == "mp4") {
            reproductorAvanzado->reproducirMp4(nombreArchivo);
        } else {
            std::cout << "[Adaptador Error] El formato '" << tipoArchivo 
                      << "' no es soportado por el adaptador." << std::endl;
        }
    }
};

// 4. Cliente / Sistema Principal

class ReproductorMusica : public ReproductorAudio {
private:
    std::unique_ptr<AdaptadorAudio> adaptador;

public:
    void reproducir(const std::string& tipoArchivo, const std::string& nombreArchivo) override {
        // Reproducción nativa para MP3
        if (tipoArchivo == "mp3") {
            std::cout << "[Nativo MP3] Reproduciendo archivo: " << nombreArchivo << std::endl;
        } 
        // Delegación al adaptador para formatos externos no nativos
        else if (tipoArchivo == "vlc" || tipoArchivo == "mp4") {
            adaptador = std::make_unique<AdaptadorAudio>();
            adaptador->reproducir(tipoArchivo, nombreArchivo);
        } else {
            std::cout << "[Sistema Error] Formato no soportado: " << tipoArchivo << std::endl;
        }
    }
};

// Punto de Entrada Principal (Main)

int main() {
    std::cout << "==================================================" << std::endl;
    std::cout << "     SISTEMA DE AUDIO INTEGRADO - GRUPO 4         " << std::endl;
    std::cout << "==================================================" << std::endl << std::endl;

    ReproductorMusica reproductor;

    // Pruebas de ejecución
    reproductor.reproducir("mp3", "cancion_favorita.mp3");
    reproductor.reproducir("mp4", "concierto_en_vivo.mp4");
    reproductor.reproducir("vlc", "podcast_tecnico.vlc");
    reproductor.reproducir("wav", "efecto_sonido.wav");

    std::cout << std::endl << "==================================================" << std::endl;
    return 0;
}