/**
 *  @brief C++ header library for matrix operation inspired numpy and scipy
 *
 *  @author Atsushi Sakai
 *
 *  @license MIT
 *
 **/
#include "Eigen/Core"

#define PRINT(X) std::cout << #X << ":\n" << X << std::endl << std::endl

/**
 * @brief  Gives a new shape to an array without changing its data.
 *         This function is based on numpy.reshape 
 *         see: https://docs.scipy.org/doc/numpy/reference/generated/numpy.reshape.html
 *
 * @param x input matrix
 * @param r the number of row elements
 * @param c the number of collum elements
 *
 * @return The new shape matrix
 */
Eigen::MatrixXf reshape(
    Eigen::MatrixXf &x,
    uint32_t r,
    uint32_t c
    ){

    Eigen::Map<Eigen::MatrixXf> rx(x.data(), r, c);
  
    return rx;
}



/**
 * @brief Detemine if matrix is diagonal
 *        if matrix is not square, return false
 *
 *        It is inspired by MATLAB isdiag function.
 *        see: https://www.mathworks.com/help/matlab/ref/isdiag.html
 *
 * @param x input matrix
 *
 * @return matrix is diagonal (true) or not (false)
 */
bool isdiag(const Eigen::MatrixXf &x){

  if(x.cols()!=x.rows()){
    return false;//not square matrix
  }

  Eigen::MatrixXf t = x.diagonal().asDiagonal();
  // PRINT(t);
 
  // std::cout<<std::abs((t-x).sum())<<std::endl;
  if(std::abs((t-x).sum())>=0.00001){
    return false;
  }

  return true;

}


/**
 * @brief Stack matrix in sequence vertically
 *        imspired by numpy.vstack
 *        https://docs.scipy.org/doc/numpy/reference/generated/numpy.vstack.html
 *
 * @param m1 first matrix
 * @param m2 second matrix
 *
 * @return stacked matrix
 */
Eigen::MatrixXf vstack(
    const Eigen::MatrixXf &m1,
    const Eigen::MatrixXf &m2
    ){

    if(m1.rows() == 0){
      return m2;
    }
    else if(m2.rows() == 0){
      return m1;
    }

    uint32_t ncol = m1.cols();
    if(ncol == 0){
      ncol = m2.cols();
    }

    Eigen::MatrixXf rm(m1.rows()+m2.rows(), ncol);
    rm << m1, m2;
  
    return rm;
}


/**
 * @brief Stack matrix in sequence horizontally
 *        imspired by numpy.hstack
 *        https://docs.scipy.org/doc/numpy/reference/generated/numpy.hstack.html
 *
 * @param m1 first matrix
 * @param m2 second matrix
 *
 * @return stacked matrix
 */
Eigen::MatrixXf hstack(
    const Eigen::MatrixXf &m1,
    const Eigen::MatrixXf &m2
    ){

    if(m1.cols() == 0){
      return m2;
    }
    else if(m2.cols() == 0){
      return m1;
    }

    uint32_t nrow = m1.rows();
    if(nrow == 0){
      nrow = m2.rows();
    }

    Eigen::MatrixXf rm(nrow, m1.cols()+m2.cols());
    rm << m1, m2;
  
    return rm;
}



/**
 * @brief Create a block diagonal matrix from provided matrices
 *        3 input version
 *        inspired scipy.linalg.block_diag
 *        https://docs.scipy.org/doc/scipy-0.14.0/reference/generated/scipy.linalg.block_diag.html
 *
 * @param m1 first matrix
 * @param m2 second matrix
 *
 * @return Created a block diagonal matrix
 */
Eigen::MatrixXf block_diag(
    const Eigen::MatrixXf &m1,
    const Eigen::MatrixXf &m2
    ){

    uint32_t m1r=m1.rows();
    uint32_t m1c=m1.cols();
    uint32_t m2r=m2.rows();
    uint32_t m2c=m2.cols();

    Eigen::MatrixXf mf = Eigen::MatrixXf::Zero(m1r + m2r , m1c + m2c);
    mf.block(0, 0, m1r, m1c) = m1;
    mf.block(m1r, m1c, m2r, m2c) = m2;
  
    return mf;
}

/**
 * @brief Create a block diagonal matrix from provided matrices
 *        3 input version
 *
 * @param m1 first matrix
 * @param m2 second matrix
 * @param m3 third matrix
 *
 * @return Created a block diagonal matrix
 */
Eigen::MatrixXf block_diag(
    const Eigen::MatrixXf &m1,
    const Eigen::MatrixXf &m2,
    const Eigen::MatrixXf &m3
    ){

  uint32_t m1r=m1.rows();
  uint32_t m1c=m1.cols();
  uint32_t m2r=m2.rows();
  uint32_t m2c=m2.cols();
  uint32_t m3r=m3.rows();
  uint32_t m3c=m3.cols();

  Eigen::MatrixXf bdm = Eigen::MatrixXf::Zero(m1r + m2r + m3r , m1c + m2c + m3c);
  bdm.block(0, 0, m1r, m1c) = m1;
  bdm.block(m1r, m1c, m2r, m2c) = m2;
  bdm.block(m1r+m2r, m1c+m2c, m3r, m3c) = m3;

  return bdm;
}



/**
 * @brief Compute the Kronecker product
 *        A composite array made of blocks of the second array scaled by the first
 *        Inspired numpy.kron
 *        see: https://docs.scipy.org/doc/numpy/reference/generated/numpy.kron.html
 *
 * @param m1 first matrix
 * @param m2 second matrix
 *
 * @return A result of the Kronecker product
 */
Eigen::MatrixXf kron(
    const Eigen::MatrixXf &m1,
    const Eigen::MatrixXf &m2
    ){

  uint32_t m1r=m1.rows();
  uint32_t m1c=m1.cols();
  uint32_t m2r=m2.rows();
  uint32_t m2c=m2.cols();
 
  
  Eigen::MatrixXf m3(m1r*m2r, m1c*m2c);
  // PRINT(m3);
 

  for (int i = 0; i < m1r; i++) {
    for (int j = 0; j < m1c; j++) {
      m3.block(i*m2r, j*m2c, m2r, m2c) =  m1(i,j)*m2;
    }
  }

  return m3;
}
