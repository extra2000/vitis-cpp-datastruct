# Changelog

## [1.2.1](https://github.com/extra2000/vitis-cpp-datastruct/compare/v1.2.0...v1.2.1) (2022-08-18)


### Documentations

* **README:** remove duplicated `.\Debug\helloworld.exe` ([df2c990](https://github.com/extra2000/vitis-cpp-datastruct/commit/df2c99019645f4d42a2a3a0537de1e24bebc6da2))
* **README:** simplify `cmake.exe` path by using `Developer PowerShell for VS 2022` ([d737980](https://github.com/extra2000/vitis-cpp-datastruct/commit/d737980ca0b2b3c109cb49d38b93fb847439922f))

## [1.2.0](https://github.com/extra2000/vitis-cpp-datastruct/compare/v1.1.0...v1.2.0) (2022-08-17)


### Features

* **CMakeLists.txt:** add support for Visual Studio 2022 on Windows 11 ([46e9948](https://github.com/extra2000/vitis-cpp-datastruct/commit/46e994838898369264543db9313a64f4aedff9be))
* **logger:** prefix public access with `DllExport` which is required to support Visual Studio 2022 on Windows 11 ([9fce30d](https://github.com/extra2000/vitis-cpp-datastruct/commit/9fce30d15acd4482cc5c3942b277986ee59b2fa7))


### Documentations

* **README:** add AppVeyor badge ([40fc236](https://github.com/extra2000/vitis-cpp-datastruct/commit/40fc236d5b46bbc371e46bff8adf926a4420f283))
* **README:** add instructions to build with Visual Studio 2022 on Windows 11 ([0801d54](https://github.com/extra2000/vitis-cpp-datastruct/commit/0801d54e3aa15da01287ba7496c2e5d8af95bcba))
* **README:** add missing `--cfgfile test.cfg` to `./datastruct_file_operations` ([2493680](https://github.com/extra2000/vitis-cpp-datastruct/commit/24936802bd82a4b1e4b47b9d1a89c9ad8145806f))
* **README:** improve `Known Issues` explanation ([46a1751](https://github.com/extra2000/vitis-cpp-datastruct/commit/46a1751fc5c7f52d2077c836e2d48e50c8c4c2fb))


### Code Refactoring

* **.gitignore:** ignore `.vs` directory ([fe8438c](https://github.com/extra2000/vitis-cpp-datastruct/commit/fe8438cddc32ecf6d4c96457369702b79309f024))
* **CMakeLists.txt:** prefix libraries with `Boost::` ([9cf1cfe](https://github.com/extra2000/vitis-cpp-datastruct/commit/9cf1cfef3df0f808a8e9d8ef03f7978d5ae37025))


### Fixes

* **datastruct_file_operations:** fix "'ofstream' is not a member of 'boost::filesystem'" ([6fbbc5c](https://github.com/extra2000/vitis-cpp-datastruct/commit/6fbbc5c6b7b67f4c0fcbdfc56e40998c3e68fe33))

## [1.1.0](https://github.com/extra2000/vitis-cpp-datastruct/compare/v1.0.0...v1.1.0) (2022-08-15)


### Features

* **example:** add `datastruct_async_signal` ([eb95825](https://github.com/extra2000/vitis-cpp-datastruct/commit/eb95825302707046d22b1a44f373ec36ccc73786))
* **example:** add `datastruct_async_timer` ([853021a](https://github.com/extra2000/vitis-cpp-datastruct/commit/853021ae59cada7fa78926481159d9f54fa34a01))
* **example:** add `datastruct_thread_timer_class` ([5b91862](https://github.com/extra2000/vitis-cpp-datastruct/commit/5b918628315300e2a6bdf31232966843bfbd01de))
* **example:** add `datastruct_thread_timer` ([92c2116](https://github.com/extra2000/vitis-cpp-datastruct/commit/92c2116a283963ec9f5cfc5a60b113d8089f7f9b))
* **podman:** add `CMakeLists.txt` and `Dockerfile` for x86 ([d12a9e9](https://github.com/extra2000/vitis-cpp-datastruct/commit/d12a9e969d148b9d7142159a318aaaf3cae22e5f))


### Styles

* **brackets:** move brackets into their own line ([4e011ed](https://github.com/extra2000/vitis-cpp-datastruct/commit/4e011ede1f88cc0efa8f59a0d83bfe8498f3bcae))
* **comments:** add missing comments ([ddd6b7f](https://github.com/extra2000/vitis-cpp-datastruct/commit/ddd6b7fd6d9d2727c905113f2e020fb802a3d308))


### Continuous Integrations

* **AppVeyor:** add instructions for building `CMakeLists.txt` with Podman ([733824d](https://github.com/extra2000/vitis-cpp-datastruct/commit/733824dacf60f2f83ae7775fc6b71eca5448e223))


### Documentations

* **README:** add instruction to use `systemd` as `init-manager` ([ac80325](https://github.com/extra2000/vitis-cpp-datastruct/commit/ac8032568a9dd8fa0f9cc4bbb7c3694ef785be33))
* **README:** improve `Known Issues` description ([45c2730](https://github.com/extra2000/vitis-cpp-datastruct/commit/45c27309bebbd1caf7827ef9c2a0a0d7df01a652))

## 1.0.0 (2022-06-19)


### Features

* initial implementations ([9853048](https://github.com/extra2000/vitis-cpp-datastruct/commit/9853048da9950cbb7d1090608e4481d8072bb1ca))


### Documentations

* **README:** update `README.md` ([d85aee1](https://github.com/extra2000/vitis-cpp-datastruct/commit/d85aee1ef5b27040fe24c9210e29b9994c318d66))


### Continuous Integrations

* add AppVeyor with `semantic-release` ([290d5ca](https://github.com/extra2000/vitis-cpp-datastruct/commit/290d5ca02a205ff137cd53ee87912d75c405452d))
