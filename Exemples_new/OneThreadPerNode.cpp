# include <thread>
# include <iostream>
# include <mutex>
# include <vector>

int main(int argc, const char** argv) {
  unsigned num_cpus = std::thread::hardware_concurrency();
  std::cout << "Créer " << num_cpus << " threads\n";
  // mutex permettant un accès ordonnées à std::cout pour les threads
  std::mutex iomutex;
  std::vector<std::thread> threads(num_cpus);
  for (unsigned i = 0; i < num_cpus; ++i) {
    // On lance un thread exécutant une lambda fonction :
    threads[i] = std::thread([&iomutex, i] ()  {
      {
        // std::lock_guard permet de bloquer un mutex pendant la durée d'un bloc
        // d'instruction. Ici cela permet de bloquer le mutex uniquement durant
        // l'affichage à l'iade de std::cout
        std::lock_guard<std::mutex> iolock(iomutex);
        std::cout << "Thread #" << i << " is running\n";
      }
      // On simule un travail important en mettant le thread un peu en pause
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
    });
  }
  for (auto& t : threads) { t.join(); }
  return 0;
} 
