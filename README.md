# McIntyre, Richardson, and Grill Axon Model

Reimplementation of the axon model from McIntyre, Richardson, and Grill (2002) in C++.


## Usage

mrg_axon_model &lt;axon file&gt; &lt;V_fe (mV)&gt; &lt;V_applied (mV)&gt; &lt;duration (ms)&gt; &lt;stim start (ms)&gt; &lt;stim end (ms)&gt;

The axon file is in the format (tab separated): &lt;x (m)&gt; &lt;y (m)&gt; &lt;z (m)&gt; &lt;Ve_pulse (V)&gt;


## History

The original implementation was in NEURON, published in:

McIntyre, C., Richardson, A. & Grill, W. (2002). Modeling the excitability of mammalian nerve ﬁbers: Inﬂuence of after potentials on the recovery cycle. J. Neurophysiol., 87, 995–1006.

It was then reimplemented in MATLAB, published at:

https://code.google.com/p/mrg-matlab/

This is a reimplementation of the MATLAB code (also found in ./reference/) in C++.
