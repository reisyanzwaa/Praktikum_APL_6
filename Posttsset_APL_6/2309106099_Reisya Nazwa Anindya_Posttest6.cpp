#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

struct Pengunjung {
    string nama;
    int nim;
    int umur;
    string alamat;
    string nomor_hp;
    string jenis_ps;
    int jam_awal_peminjaman;
    int lama_peminjaman;
    int jam_pengembalian;
};

vector<Pengunjung> daftarPengunjung;

// Fungsi Sequential Search Ascending
int sequentialSearchAscending(const vector<Pengunjung> &arr, int target) {
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i].nim == target) {
            return i; // Mengembalikan indeks jika ditemukan
        }
    }
    return -1; // Mengembalikan -1 jika tidak ditemukan
}

// Fungsi Sequential Search Descending
int sequentialSearchDescending(const vector<Pengunjung> &arr, int target) {
    for (int i = arr.size() - 1; i >= 0; --i) {
        if (arr[i].nim == target) {
            return i; // Mengembalikan indeks jika ditemukan
        }
    }
    return -1; // Mengembalikan -1 jika tidak ditemukan
}

// Fungsi Binary Search Ascending
int binarySearchAscending(const vector<Pengunjung> &arr, int target) {
    int low = 0;
    int high = arr.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid].nim == target) {
            return mid; // Mengembalikan indeks jika ditemukan
        } else if (arr[mid].nim < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1; // Mengembalikan -1 jika tidak ditemukan
}

// Fungsi Binary Search Descending
int binarySearchDescending(const vector<Pengunjung> &arr, int target) {
    int low = 0;
    int high = arr.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid].nim == target) {
            return mid; // Mengembalikan indeks jika ditemukan
        } else if (arr[mid].nim > target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1; // Mengembalikan -1 jika tidak ditemukan
}

void tampilkanMenuUtama();
bool loginAdmin();
void tampilkanMenuAdmin();
void tampilkanMenuPengunjung();
void tampilkanBiodata(const Pengunjung &pengunjung);
void tambahPengunjung();
void hapusPengunjung();
void editPengunjung();
void insertionSortAscending(vector<Pengunjung> &arr);
int partitionDescending(vector<Pengunjung> &arr, int low, int high);
void quickSortDescending(vector<Pengunjung> &arr, int low, int high);
void shellSortAscending(vector<Pengunjung> &arr);

void tampilkanMenuUtama() {
    cout << "\nMenu Utama:\n";
    cout << "1. Admin\n";
    cout << "2. Pengunjung\n";
    cout << "3. Keluar\n";
}

bool loginAdmin() {
    string nama, nim;
    int attempt = 0;
    while (attempt < 3) {
        cout << "\nMasukkan nama anda untuk login sebagai Admin:\n";
        cout << "Nama: ";
        getline(cin, nama); // Menggunakan getline() langsung
        cout << "Nim: ";
        getline(cin, nim);
        
        if (nama == "Reisya Nazwa Anindya" && nim == "2309106099") {
            cout << "Login anda berhasil sebagai Admin.\n";
            return true;
        } else {
            cout << "Nama atau Nim anda salah. Silakan dicoba lagi.\n";
            attempt++;
        }
    }
    cout << "Anda telah melebihi batas percobaan login. Kembali ke menu utama.\n";
    return false;
}

void tampilkanMenuAdmin() {
    cout << "\nMenu Admin:\n";
    cout << "1. Lihat Daftar Pengunjung\n";
    cout << "2. Tambah Pengunjung\n";
    cout << "3. Edit Pengunjung\n";
    cout << "4. Hapus Pengunjung\n";
    cout << "5. Cari Pengunjung\n"; // Tambah opsi pencarian
    cout << "6. Urutkan Daftar Pengunjung\n";
    cout << "7. Keluar\n";
}

void tampilkanMenuPengunjung() {
    cout << "\nMenu Pengunjung:\n";
    cout << "1. Isi Biodata Diri dan Peminjaman\n";
    cout << "2. Lihat Biodata dan Tagihan\n";
    cout << "3. Keluar\n";
}

void tampilkanBiodata(const Pengunjung &pengunjung) {
    cout << "\nBiodata Pengunjung:\n";
    cout << "Nama: " << pengunjung.nama << endl;
    cout << "NIM: " << pengunjung.nim << endl;
    cout << "Umur: " << pengunjung.umur << endl;
    cout << "Alamat: " << pengunjung.alamat << endl;
    cout << "Nomor HP: " << pengunjung.nomor_hp << endl;
    cout << "Jenis Peminjaman PS: " << pengunjung.jenis_ps << endl;
    cout << "Jam Awal Peminjaman: " << pengunjung.jam_awal_peminjaman << endl;
    cout << "Jam Pengembalian: " << pengunjung.jam_pengembalian << endl;
    cout << "Lama Peminjaman: " << pengunjung.lama_peminjaman << " jam" << endl;

    int harga_per_jam;
    if (pengunjung.jenis_ps == "PS3") {
        harga_per_jam = 6000;
    } else if (pengunjung.jenis_ps == "PS4") {
        harga_per_jam = 8000;
    } else if (pengunjung.jenis_ps == "PS5") {
        harga_per_jam = 12000;
    } else {
        cout << "Jenis PS tidak valid untuk pengunjung: " << pengunjung.nama << endl;
        return;
    }

    int tagihan = harga_per_jam * pengunjung.lama_peminjaman;
    cout << "Tagihan: Rp." << tagihan << endl;
}

void tambahPengunjung() {
    Pengunjung pengunjungBaru;
    cout << "\nIsi Biodata Diri dan Peminjaman Anda:\n";
    cout << "Nama: ";
    cin.ignore(); 
    getline(cin, pengunjungBaru.nama);
    cout << "NIM: ";
    while (!(cin >> pengunjungBaru.nim)) {
        cout << "Masukkan NIM dengan benar: ";
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    }
    cin.ignore(); 
    cout << "Umur: ";
    while (!(cin >> pengunjungBaru.umur)) {
        cout << "Masukkan umur dengan benar: ";
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    }
    cin.ignore(); 
    cout << "Alamat: ";
    cin.ignore(); 
    getline(cin, pengunjungBaru.alamat);
    cout << "Nomor HP: ";
    getline(cin, pengunjungBaru.nomor_hp);
    cout << "Pilih Jenis Peminjaman PS:\n";
    cout << "1. PS3\n";
    cout << "2. PS4\n";
    cout << "3. PS5\n";
    int pilihan;
    cout << "Masukkan pilihan Anda: ";
    while (!(cin >> pilihan) || pilihan < 1 || pilihan > 3) {
        cout << "Pilihan tidak valid. Masukkan kembali: ";
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    }
    cin.ignore(); 
    switch (pilihan) {
        case 1:
            pengunjungBaru.jenis_ps = "PS3";
            break;
        case 2:
            pengunjungBaru.jenis_ps = "PS4";
            break;
        case 3:
            pengunjungBaru.jenis_ps = "PS5";
            break;
    }
    
    cout << "Masukkan jam awal peminjaman: ";
    while (!(cin >> pengunjungBaru.jam_awal_peminjaman) || pengunjungBaru.jam_awal_peminjaman < 0 || pengunjungBaru.jam_awal_peminjaman > 23) {
        cout << "Masukkan jam yang valid (0-23): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Masukkan jam pengembalian: ";
    while (!(cin >> pengunjungBaru.jam_pengembalian) || pengunjungBaru.jam_pengembalian < 0 || pengunjungBaru.jam_pengembalian > 23) {
        cout << "Masukkan jam yang valid (0-23): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Masukkan lama peminjaman (dalam jam) anda: ";
    while (!(cin >> pengunjungBaru.lama_peminjaman)) {
        cout << "Masukkan lama peminjaman dengan benar: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int harga_per_jam;
    if (pengunjungBaru.jenis_ps == "PS3") {
        harga_per_jam = 6000;
    } else if (pengunjungBaru.jenis_ps == "PS4") {
        harga_per_jam = 8000;
    } else if (pengunjungBaru.jenis_ps == "PS5") {
        harga_per_jam = 12000;
    } else {
        cout << "Jenis PS tidak valid.\n";
        return;
    }

    int tagihan = harga_per_jam * pengunjungBaru.lama_peminjaman;
    cout << "Tagihan: Rp." << tagihan << endl;

    daftarPengunjung.push_back(pengunjungBaru);
    cout << "Pengunjung berhasil ditambahkan.\n";
}

void hapusPengunjung() {
    int nim;
    cout << "Masukkan NIM pengunjung yang ingin anda hapus: ";
    cin >> nim;
    bool pengunjungDitemukan = false;
    for (auto it = daftarPengunjung.begin(); it != daftarPengunjung.end(); ++it) {
        if (it->nim == nim) {
            it = daftarPengunjung.erase(it);
            cout << "Pengunjung dengan NIM " << nim << " berhasil dihapus.\n";
            pengunjungDitemukan = true;
            break;
        }
    }
    if (!pengunjungDitemukan) {
        cout << "Pengunjung dengan NIM " << nim << " tidak ditemukan.\n";
    }
}

void editPengunjung() {
    int nim;
    cout << "Masukkan NIM pengunjung yang ingin anda edit: ";
    cin >> nim;
    bool pengunjungDitemukan = false;
    for (auto &pengunjung : daftarPengunjung) {
        if (pengunjung.nim == nim) {
            cout << "\nEdit Biodata Pengunjung:\n";
            cout << "Nama: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, pengunjung.nama);
            cout << "Umur: ";
            cin >> pengunjung.umur;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Alamat: ";
            getline(cin, pengunjung.alamat);
            cout << "Nomor HP: ";
            getline(cin, pengunjung.nomor_hp);
            cout << "Pilih Jenis Peminjaman PS:\n";
            cout << "1. PS3\n";
            cout << "2. PS4\n";
            cout << "3. PS5\n";
            int pilihan;
            cout << "Masukkan pilihan Anda: ";
            cin >> pilihan;
            switch (pilihan) {
                case 1:
                    pengunjung.jenis_ps = "PS3";
                    break;
                case 2:
                    pengunjung.jenis_ps = "PS4";
                    break;
                case 3:
                    pengunjung.jenis_ps = "PS5";
                    break;
                default:
                    cout << "Pilihan tidak valid.\n";
                    continue; 
            }

            cout << "Masukkan jam awal peminjaman: ";
            while (!(cin >> pengunjung.jam_awal_peminjaman) || pengunjung.jam_awal_peminjaman < 0 || pengunjung.jam_awal_peminjaman > 23) {
                cout << "Masukkan jam yang valid (0-23): ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Masukkan jam pengembalian: ";
            while (!(cin >> pengunjung.jam_pengembalian) || pengunjung.jam_pengembalian < 0 || pengunjung.jam_pengembalian > 23) {
                cout << "Masukkan jam yang valid (0-23): ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Masukkan lama peminjaman (dalam jam) anda: ";
            while (!(cin >> pengunjung.lama_peminjaman)) {
                cout << "Masukkan lama peminjaman dengan benar: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            int harga_per_jam;
            if (pengunjung.jenis_ps == "PS3") {
                harga_per_jam = 6000;
            } else if (pengunjung.jenis_ps == "PS4") {
                harga_per_jam = 8000;
            } else if (pengunjung.jenis_ps == "PS5") {
                harga_per_jam = 12000;
            } else {
                cout << "Jenis PS tidak valid.\n";
                continue;
            }

            int tagihan = harga_per_jam * pengunjung.lama_peminjaman;
            cout << "Tagihan: Rp." << tagihan << endl;

            cout << "Biodata pengunjung berhasil diperbarui.\n";
            pengunjungDitemukan = true;
            break;
        }
    }
    if (!pengunjungDitemukan) {
        cout << "Pengunjung dengan NIM " << nim << " tidak ditemukan.\n";
    }
}

int partitionDescending(vector<Pengunjung> &arr, int low, int high) {
    Pengunjung pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j].jam_awal_peminjaman > pivot.jam_awal_peminjaman) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSortDescending(vector<Pengunjung> &arr, int low, int high) {
    if (low < high) {
        int pi = partitionDescending(arr, low, high);
        quickSortDescending(arr, low, pi - 1);
        quickSortDescending(arr, pi + 1, high);
    }
}

void insertionSortAscending(vector<Pengunjung> &arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        Pengunjung key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].jam_awal_peminjaman > key.jam_awal_peminjaman) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void shellSortAscending(vector<Pengunjung> &arr) {
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i += 1) {
            Pengunjung temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap].jam_awal_peminjaman > temp.jam_awal_peminjaman; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

int main() {
    while (true) {
        tampilkanMenuUtama();
        int pilihan;
        cout << "Masukkan pilihan Anda: ";
        while (!(cin >> pilihan)) {
            cout << "Pilihan tidak valid. Masukkan kembali: ";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
        
        switch (pilihan) {
            case 1: {
                if (loginAdmin()) {
                    bool keluarAdmin = false;
                    while (!keluarAdmin) {
                        tampilkanMenuAdmin();
                        cout << "Masukkan pilihan Anda: ";
                        int pilihanAdmin;
                        while (!(cin >> pilihanAdmin)) {
                            cout << "Pilihan tidak valid. Masukkan kembali: ";
                            cin.clear(); 
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                        }
                        switch (pilihanAdmin) {
                            case 1:
                                if (daftarPengunjung.empty()) {
                                    cout << "Daftar pengunjung masih kosong.\n";
                                } else {
                                    cout << "\nDaftar Pengunjung:\n";
                                    for (const auto &pengunjung : daftarPengunjung) {
                                        cout << "Nama: " << pengunjung.nama << ", NIM: " << pengunjung.nim << ", Jenis PS: " << pengunjung.jenis_ps << endl;
                                    }
                                }
                                break;
                            case 2:
                                tambahPengunjung();
                                break;
                            case 3:
                                editPengunjung();
                                break;
                            case 4:
                                hapusPengunjung();
                                break;
                            case 5:
                            if (daftarPengunjung.empty()) {
                                cout << "Daftar pengunjung masih kosong.\n";
                                break;
                            }
                            int metodeSort;
                            cout << "\nPilih metode pengurutan:\n";
                            cout << "1. Quick Sort\n";
                            cout << "2. Insertion Sort\n";
                            cout << "3. Shell Sort\n";
                            cout << "Masukkan pilihan Anda: ";
                            while (!(cin >> metodeSort) || metodeSort < 1 || metodeSort > 3) {
                                cout << "Pilihan tidak valid. Masukkan kembali: ";
                                cin.clear(); 
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                            }
                            switch (metodeSort) {
                                case 1:
                                    quickSortDescending(daftarPengunjung, 0, daftarPengunjung.size() - 1);
                                    break;
                                case 2:
                                    insertionSortAscending(daftarPengunjung);
                                    break;
                                case 3:
                                    shellSortAscending(daftarPengunjung);
                                    break;
                                default:
                                    cout << "Pilihan tidak valid.\n";
                                    break;
                            }
                            cout << "Daftar pengunjung berhasil diurutkan.\n";
                            break;
          int metodePencarian;
                                cout << "Pilih metode pencarian:\n";
                                cout << "1. Sequential Search (Ascending)\n";
                                cout << "2. Sequential Search (Descending)\n";
                                cout << "3. Binary Search (Ascending)\n";
                                cout << "4. Binary Search (Descending)\n";
                                cout << "Masukkan pilihan Anda: ";
                                while (!(cin >> metodePencarian) || metodePencarian < 1 || metodePencarian > 4) {
                                    cout << "Pilihan tidak valid. Masukkan kembali: ";
                                    cin.clear(); 
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                                }

                                case 6:
                                int cariNIM;
                                cout << "Masukkan NIM yang ingin dicari: ";
                                cin >> cariNIM;
                                int hasilPencarian;
                                switch (metodePencarian) {
                                    case 1:
                                        hasilPencarian = sequentialSearchAscending(daftarPengunjung, cariNIM);
                                        break;
                                    case 2:
                                        hasilPencarian = sequentialSearchDescending(daftarPengunjung, cariNIM);
                                        break;
                                    case 3:
                                        hasilPencarian = binarySearchAscending(daftarPengunjung, cariNIM);
                                        break;
                                    case 4:
                                        hasilPencarian = binarySearchDescending(daftarPengunjung, cariNIM);
                                        break;
                                }
                                if (hasilPencarian != -1) {
                                    cout << "Pengunjung ditemukan:\n";
                                    tampilkanBiodata(daftarPengunjung[hasilPencarian]);
                                } else {
                                    cout << "Pengunjung tidak ditemukan.\n";
                                }
                                break;
                                
                            case 7:
                                keluarAdmin = true;
                                break;
                            default:
                                cout << "Pilihan tidak valid.\n";
                                break;
                        }
                    }
                }
                break;
            }
            case 2: {
                bool keluarPengunjung = false;
                while (!keluarPengunjung) {
                    tampilkanMenuPengunjung();
                    int pilihanPengunjung;
                    cout << "Masukkan pilihan Anda: ";
                    while (!(cin >> pilihanPengunjung)) {
                        cout << "Pilihan tidak valid. Masukkan kembali: ";
                        cin.clear(); 
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    }
                    switch (pilihanPengunjung) {
                        case 1:
                            tambahPengunjung();
                            break;
                        case 2:
                            if (daftarPengunjung.empty()) {
                                cout << "Anda belum menambahkan data peminjaman.\n";
                            } else {
                                int nim;
                                cout << "Masukkan NIM anda: ";
                                cin >> nim;
                                bool ditemukan = false;
                                for (const auto &pengunjung : daftarPengunjung) {
                                    if (pengunjung.nim == nim) {
                                        tampilkanBiodata(pengunjung);
                                        ditemukan = true;
                                        break;
                                    }
                                }
                                if (!ditemukan) {
                                    cout << "Data peminjaman dengan NIM " << nim << " tidak ditemukan.\n";
                                }
                            }
                            break;
                        case 3:
                            keluarPengunjung = true;
                            break;
                        default:
                            cout << "Pilihan tidak valid.\n";
                            break;
                    }
                }
                break;
            }
            case 3:
                cout << "Terima kasih telah menggunakan layanan kami. Sampai jumpa!\n";
                return 0;
            default:
                cout << "Pilihan tidak valid. Silakan pilih kembali.\n";
                break;
        }
    }

    return 0;
}
