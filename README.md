# computer-networks
Some exercises to learn how computer networks work by using Marionnet software.

## Exercises

### exercise2
Create two physically separate networks with four hosts and two switches. Each host has a network card with its IP address respectively `10.0.0.1`, `10.0.0.2`, `10.0.0.3` and `10.0.0.4`. The first network must include the first and second hosts, and the second network must have the other two.

Verify that the first host can communicate with the second host. The same applies to the third and the fourth. Also verify that the first host cannot communicate with the third host.

---

### exercise3
Repeat the setup in exercise2 using a single switch. The VLANs must use a port-based VLAN. 

Verify that everything is as in the previous case.

---

### exercise4
Repeat the setup in exercise3 using two switches. The VLANs must still use a port-based VLAN. Use a private cable for each VLAN. 

Verify that everything is as in the previous case.

---

### exercise5
Repeat the setup in exercise4 using two switches. This time the VLANs must use a tag-based VLAN. Use only one cable for both VLAN. 

Verify that everything is as in the previous case.
