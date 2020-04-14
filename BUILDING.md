## Building

### Dependencies

* Meson and Ninja build tools.
* A C11-compliant compiler, such as:
  * GCC 4.6 or later.
  * Clang 3.1 or later.
* Doxygen 1.8.8 or later.
* GraphViz 2.40.1 or later.
* Clang Format 8 or later.
* Clang Tidy 8 or later.

If you already have the dependencies installed, then you should be able to build fairly trivially.

### Build options

There are some options in `meson_options.txt`:

| Name           | Type      | Values                         |
|----------------|-----------|--------------------------------|
| `enable-tests` | `boolean` | `true` - enables testing       |
|                |           | `false` - disables testing     |
| `domain-type`  | `combo`   | `ipv4` - compile ipv4 netcode  |

### Linux building

```
$ meson . build
$ ninja -C build
```

### Generating documentation

```
$ ninja -C build docs
```

### Applying Clang format & Clang tidy

```
$ ninja -C build clang-format
$ ninja -C build clang-tidy
```