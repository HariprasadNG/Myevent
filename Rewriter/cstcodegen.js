function rwMemberExpression (expr, precedence, flags) {
  var result, fragment;
  var wrap = false;
  var obj = this.generateExpression(expr.object, cstcodegen.m_code.Precedence.Call, flags & cstcodegen.m_code.F_ALLOW_CALL ? cstcodegen.m_code.E_TTF : cstcodegen.m_code.E_TFF);
  if (true && /location/.test(obj)) {
        wrap = true;
  }
  if (wrap) {
    result = ['DSMemberGet(' + obj + ','];
  } else {
      result = [obj];
  }
  if (expr.computed) {
     if (!wrap) result.push('[')
    result.push(this.generateExpression(expr.property,cstcodegen.m_code.Precedence.Sequence, flags & cstcodegen.m_code.F_ALLOW_CALL ? cstcodegen.m_code.E_TTT : cstcodegen.m_code.E_TFT));
    if (!wrap) {
        result.push(']');
    } else {
        result.push(')');
    }
  } else {
    if (expr.object.type === cstcodegen.m_code.Syntax.Literal && typeof expr.object.value === 'number') {
      fragment = this.toSourceNodeWhenNeeded(result).toString();
      if (fragment.indexOf('.') < 0 && !/[eExX]/.test(fragment) && this.esutils.code.isDecimalDigit(fragment.charCodeAt(fragment.length - 1)) && !(fragment.length >= 2 && fragment.charCodeAt(0) === 48)) {
        result.push('.');
      }
    }
    if(wrap) {
      result.push('"');
    } else {
      result.push('.');
    }
    result.push(cstcodegen.m_code.generateIdentifier(expr.property));
    if(wrap)result.push('")');
  }
  return cstcodegen.m_code.parenthesize(result, cstcodegen.m_code.Precedence.Member, precedence);
}

function rwUpdateExpression (expr, precedence, flags) {
 if (expr.argument.type == "MemberExpression") {
     var obj = this.generateExpression(expr.argument.object, 
                             cstcodegen.m_code.Precedence.Call, 
                             flags & cstcodegen.m_code.F_ALLOW_CALL ? cstcodegen.m_code.E_TTF:cstcodegen.m_code.E_TTF);
     var prp = this.generateExpression(expr.argument.property,
                             cstcodegen.m_code.Precedence.Sequence, 
                             flags & cstcodegen.m_code.F_ALLOW_CALL ? cstcodegen.m_code.E_TTF:this.E_TTF);
     if (!expr.argument.computed) {
         prp = "'" + prp + "'";
     }
    return cstcodegen.m_code.parenthesize([
      'DSMemberGetNUpdate(',
          expr.prefix,
          ',', 
          obj,
          ',', 
          prp,
          ',"',
          expr.operator, 
          '")'
    ], cstcodegen.m_code.Precedence.Unary, precedence);
 } else {
     return this.orgUpdateExpression(expr, precedence, flags);
 }
}

function rwNewExpression (e, p, f) {
    UnHookFunctions.apply(this,[]);
    var ret = this.orgNewExpression(e, p, f);
    HookFunctions.apply(this,[]);
    return ret;
}

function rwFunctionExpression (e, p, f) {
    UnHookFunctions.apply(this,[]);
    var x = this.orgFunctionExpression(e, p, f);
    HookFunctions.apply(this,[]);
    return x;
}

function rwBinaryExpression(e, p, f) {
    HookFunctions.call(this);
    var x = this.orgBinaryExpression(e, p, f);
    UnHookFunctions.call(this);
    return x;
}

function HookFunctions() {
    if (this.orgMemberExpression == null) this.orgMemberExpression  = this.MemberExpression;
    this.MemberExpression = rwMemberExpression;
    if (this.orgUpdateExpression == null) this.orgUpdateExpression = this.UpdateExpression;
    this.UpdateExpression = rwUpdateExpression;
}

function UnHookFunctions() {
    //this.MemberExpression = this.orgMemberExpression?this.orgMemberExpression:this.MemberExpression;
    //this.UpdateExpression = this.orgUpdateExpression?this.orgUpdateExpression:this.UpdateExpression;
}

var cstcodegen = {
    m_code:null,
    OverrideCodeGen:function (code) {
        cstcodegen.m_code = code;
        var space = '';
        code.CodeGenerator.prototype.generateAssignment = function (left, right, operator, precedence, flags) {
            HookFunctions.apply(this, []);
            if (code.Precedence.Assignment < precedence) {
              flags |= code.F_ALLOW_IN;
            }
            if (left && left.type == 'MemberExpression') {
                var memParam = this.generateExpression(left.property);
                if (!left.computed) {
                    memParam = '"' + memParam +'"';
                }
                HookFunctions.apply(this,[]);
                var rightExp = this.generateExpression(right, code.Precedence.Assignment, flags);
                UnHookFunctions.apply(this,[]);

                return code.parenthesize (
                ["DSAssign("  
                + this.generateExpression(left.object, code.Precedence.Assignment,flags) + "," 
                + memParam + "," + "'" + operator + "',"
                + rightExp + ")"
                ], code.Precedence.Assignment, precedence);
            } 
            HookFunctions.apply(this,[]);
            var rightExp = this.generateExpression(right, code.Precedence.Assignment, flags);
            UnHookFunctions.apply(this,[]);

            return code.parenthesize([
              this.generateExpression(left, code.Precedence.Call, flags),
              space + operator + space,
              rightExp
            ], code.Precedence.Assignment, precedence);
        };

        code.CodeGenerator.prototype.CallExpression = function (expr, precedence, flags) {
            HookFunctions.call(this);
            var result, i, iz;
            var rewrite = false;
            // F_ALLOW_UNPARATH_NEW becomes false.
            if (expr.callee.type == 'MemberExpression') {
                var memParam = this.generateExpression(expr.callee.property);
                rewrite = true;
                if (!expr.callee.computed) {
                    memParam = '"' + memParam + '"';
                }
                result = ['DSMemberFuncCall(' + this.generateExpression(expr.callee.object, code.Precedence.Assignment, flags) + ',' + memParam + ',['];
            } else {
                result = [this.generateExpression(expr.callee, code.Precedence.Call, code.E_TTF)];
                result.push('(');
            }
            for (i = 0, iz = expr['arguments'].length; i < iz; ++i) {
                result.push(this.generateExpression(expr['arguments'][i], code.Precedence.Assignment, code.E_TTT));
                if (i + 1 < iz) {
                    result.push(',' + space);
                }
            }
            if (rewrite) {
                result.push('])');
            } else {
                result.push(')');
            }

            if (!(flags & code.F_ALLOW_CALL)) {
                UnHookFunctions.call(this);
                return ['(', result, ')'];
            }
            var ret =  code.parenthesize(result, code.Precedence.Call, precedence);
            UnHookFunctions.call(this);
            return ret;
        };

        code.CodeGenerator.prototype.VariableDeclarator = function (stmt, flags) {
          var itemFlags = flags & code.F_ALLOW_IN ? code.E_TTT : code.E_FTT;
          if (stmt.init) {
            HookFunctions.apply(this,[]);
            var rightExp = this.generateExpression(stmt.init, code.Precedence.Assignment, itemFlags)
            UnHookFunctions.apply(this, []);
            return [
              this.generateExpression(stmt.id, code.Precedence.Assignment, itemFlags),
              space,
              '=',
              space,
              rightExp];
          }
          return this.generatePattern(stmt.id, code.Precedence.Assignment, itemFlags);
        }

        if (code.CodeGenerator.prototype.orgFunctionExpression == null) {
            code.CodeGenerator.prototype.orgFunctionExpression = code.CodeGenerator.prototype.FunctionExpression;
            code.CodeGenerator.prototype.FunctionExpression = rwFunctionExpression;
        } 
        
        if (code.CodeGenerator.prototype.orgNewExpression == null) {
            code.CodeGenerator.prototype.orgNewExpression = code.CodeGenerator.prototype.NewExpression;
            code.CodeGenerator.prototype.NewExpression = rwNewExpression;
        } 

        if (code.CodeGenerator.prototype.orgBinaryExpression == null) {
            code.CodeGenerator.prototype.orgBinaryExpression = code.CodeGenerator.prototype.BinaryExpression;
            code.CodeGenerator.prototype.BinaryExpression = rwBinaryExpression;
        } 
        return code;
    }
};

module.exports = {
    OverrideCodeGen:cstcodegen.OverrideCodeGen
}
