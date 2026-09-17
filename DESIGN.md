# Error Handling Design
Use both:
  - return values
  - XeonC_errno
Use goto cleanup, preferred to keep it simple with explainable control flow.

# UB design
minimum aliasing.
integrate ownership into the coding logic.
assume worst out of C strings