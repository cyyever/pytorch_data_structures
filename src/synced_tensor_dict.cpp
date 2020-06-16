#include <cyy/cpp_lib/torch/synced_sparse_tensor_dict.hpp>
#include <cyy/cpp_lib/torch/synced_tensor_dict.hpp>
#include <torch/extension.h>
PYBIND11_MODULE(TORCH_EXTENSION_NAME, m) {
  using synced_tensor_dict = cyy::cxx_lib::pytorch::synced_tensor_dict;
  using synced_sparse_tensor_dict =
      cyy::cxx_lib::pytorch::synced_sparse_tensor_dict;
  auto sub_m = m.def_submodule("data_structure", "Contains data structures");
  py::class_<synced_tensor_dict>(sub_m, "SyncedTensorDict")
      .def(py::init<const std::string &>())
      .def("prefetch", (void (synced_tensor_dict::*)(
                           const std::vector<std::string> &keys)) &
                           synced_tensor_dict::prefetch)
      .def("set_in_memory_number", &synced_tensor_dict::set_in_memory_number)
      .def("set_storage_dir", &synced_tensor_dict::set_storage_dir)
      .def("get_storage_dir", &synced_tensor_dict::get_storage_dir)
      .def("set_permanent_storage",
           &synced_tensor_dict::enable_permanent_storage)
      .def("enable_permanent_storage",
           &synced_tensor_dict::enable_permanent_storage)
      .def("disable_permanent_storage",
           &synced_tensor_dict::disable_permanent_storage)
      .def("set_wait_flush_ratio", &synced_tensor_dict::set_wait_flush_ratio)
      .def("set_saving_thread_number",
           &synced_tensor_dict::set_saving_thread_number)
      .def("set_fetch_thread_number",
           &synced_tensor_dict::set_fetch_thread_number)
      .def("enable_debug_logging", &synced_tensor_dict::enable_debug_logging)
      .def("__setitem__", &synced_tensor_dict::emplace)
      .def("__len__", &synced_tensor_dict::size)
      .def("__contains__", &synced_tensor_dict::contains)
      .def("__getitem__", &synced_tensor_dict::get)
      .def("__delitem__", &synced_tensor_dict::erase)
      .def("keys", &synced_tensor_dict::keys)
      .def("release", &synced_tensor_dict::release)
      .def("flush_all", &synced_tensor_dict::flush_all,
           "flush all in-memory data to the disk", py::arg("wait") = false)
      .def("flush",
           (void (synced_tensor_dict::*)()) & synced_tensor_dict::flush);
  py::class_<synced_sparse_tensor_dict, synced_tensor_dict>(
      sub_m, "SyncedSparseTensorDict")
      .def(py::init<torch::Tensor, torch::IntArrayRef, const std::string &>())
      .def("__getitem__", &synced_sparse_tensor_dict::get)
      .def("__setitem__", &synced_sparse_tensor_dict::emplace);
}
