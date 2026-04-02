# tree-inventory-benchmarking-c
Tree Inventory Management: Memory Performance Benchmarking
Repositori ini berisi implementasi sistem manajemen inventaris pohon menggunakan bahasa C, dengan dua arsitektur memori yang berbeda: Singly Linked List dan Dynamic Array. Fokus utama proyek ini adalah melakukan automated benchmarking untuk memvalidasi efisiensi algoritma pada skala data yang berbeda.

🚀 Key Features
Dual Architecture Implementation: Menangani alokasi memori dinamis untuk data pohon (ID, Spesies, GPS, Umur, Diameter).

Automated Testbench: Menggunakan Python untuk mengotomatisasi kompilasi GCC, eksekusi program, dan ekstraksi metrik performa.

Reproducibility: Seluruh alur kerja terintegrasi dalam satu Jupyter Notebook (.ipynb).

Performance Metrics: Analisis mendalam terhadap Memory Usage, Execution Time, dan Throughput (ops/s).

📊 Performance Analysis Summary
Berdasarkan hasil pengujian pada skala data Large (200.000 entri):

Operation	Best Performer	Rationale
Add	Dynamic Array	O(1) amortized vs O(N) tail traversal pada Linked List.
View	Dynamic Array	Keunggulan CPU Cache Spatial Locality pada memori kontigu.
Delete	Linked List	Operasi pointer O(1) menghindari penalti memory shifting O(N).
🛠 Project Structure
PR5_Build/: Folder output berisi source code C, binaries, dan hasil CSV.

PR5_Architecture_Analysis.ipynb: Notebook utama untuk replikasi eksperimen.

linkedlist.c & array.c: Core engine sistem dalam bahasa C.

🏁 How to Run
Pastikan Anda memiliki gcc (Compiler C) dan Python 3 terinstal.

Buka PR5_Architecture_Analysis.ipynb di VS Code atau Jupyter.

Jalankan seluruh cells. Hasil analisis akan otomatis tersimpan di folder PR5_Build/.
