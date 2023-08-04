# SvE-Chorus
This repository contains a template plugin for building plugins using the DPF framework.
Template plugin is build using the example plugins from DPF made by FalkTX.

Clone git repository
```
git clone git@github.com:StevenRVE/sve-template-plugin.git
```

Add DPF as git submodule
```
cd sve-chorus

git submodule add -b develop --name dpf git@github.com:DISTRHO/DPF.git dpf
git submodule update --init --recursive

cd dpf
git pull
```

If something is wrong with adding dpf, remove the submodule following the steps described here: https://gist.github.com/myusuf3/7f645819ded92bda6677#:~:text=To%20remove%20a,upvote%20this%20answer

##Generate new template plugin

```
cd source

python generateNewPlugin.py
```

Enter name and URI in terminal

<!-- TODO: Update this section with instructions for Marc/Ciska how to build and test plugin -->

### Bibliography:
- Hack Audio: An Introduction to Computer Programming and Digital Signal Processing in MATLAB, by Eric Tarr
- Designing Audio Effect Plugins in C++, by Will Pirkle
- musicdsp.org
- https://www.geeksforgeeks.org/new-vs-malloc-and-free-vs-delete-in-c/