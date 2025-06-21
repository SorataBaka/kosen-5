import matplotlib.pyplot as plt
import numpy as np

def load_data(filename):
    return np.loadtxt(filename)

def plot_waveform(time, amplitude, title, xlabel, ylabel, filename):
    plt.figure()
    plt.plot(time, amplitude)
    plt.title(title)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(filename)
    print(f"Saved plot: {filename}")

def main():
    # Waveform (original)
    wf = load_data("wf.txt")
    plot_waveform(
        wf[:,0], wf[:,1],
        "Original Waveform",
        "Time [s]", "Amplitude",
        "waveform.png"
    )

    # DFT magnitude
    dft = load_data("dft.txt")
    plot_waveform(
        dft[:,0], dft[:,1],
        "DFT Magnitude Spectrum",
        "Frequency [Hz]", "Magnitude",
        "dft_magnitude.png"
    )

    # IDFT (reconstructed waveform)
    idft = load_data("idft.txt")
    plot_waveform(
        idft[:,0], idft[:,1],
        "Reconstructed Waveform (IDFT)",
        "Time [s]", "Amplitude",
        "idft_waveform.png"
    )
    # FFT (reconstructed waveform)
    fft = load_data("fft.txt")
    plot_waveform(
        fft[:,0], fft[:,1],
        "FFT Magnitude Spectrum",
        "Frequency [Hz]", "Magnitude",
        "fft_magnitude.png"
    )

if __name__ == "__main__":
    main()
